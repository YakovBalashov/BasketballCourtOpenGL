#include "../../include/Rendering/Model.h"

#include <iostream>

Model::Model(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Assimp load error: " << importer.GetErrorString() << std::endl;
        throw std::runtime_error("Assimp load error: " + std::string(importer.GetErrorString()));
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::Render() const
{
    for (const auto& mesh : meshes) {
        mesh->Render();
    }
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Mesh> Model::ProcessMesh(const aiMesh* mesh)
{
    std::vector<float> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        const aiVector3D& v = mesh->mVertices[i];
        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return std::make_shared<Mesh>(
        vertices.data(), indices.data(), static_cast<int>(vertices.size() * sizeof(float)), static_cast<int>(indices.size() * sizeof(unsigned int))
    );
}
