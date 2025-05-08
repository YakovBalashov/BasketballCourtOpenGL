#include "../../include/Rendering/Model.h"

#include <iostream>

#include "Rendering/Texture.h"

Model::Model(const std::string& path)
{
    directory = path.substr(0, path.find_last_of('/'));
    Assimp::Importer importer;
    importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

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
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, const char* typeName)
{
    std::vector<std::shared_ptr<Texture>> textures; 

    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i) {
        aiString str;
        material->GetTexture(type, i, &str);
        std::string pathFromAssimp = std::string(str.C_Str());

        for (char &c : pathFromAssimp) {
            if (c == '\\') c = '/';
        }

        bool foundInCache = false;
        for (const auto& cached_texture : loadedTextures) {
            if (cached_texture->path == pathFromAssimp) {
                textures.push_back(cached_texture);
                foundInCache = true;
                std::cout << "Texture (Assimp path: [" << pathFromAssimp << "]) found in cache." << std::endl;
                break;
            }
        }

        if (foundInCache) continue; 

        std::string baseFilename = pathFromAssimp;
        size_t lastSlash = baseFilename.find_last_of('/');
        if (lastSlash != std::string::npos) {
            baseFilename = baseFilename.substr(lastSlash + 1);
        }

        if (baseFilename.empty()) {
            std::cerr << "Extracted empty base filename from Assimp path: [" << pathFromAssimp << "]" << std::endl;
            continue;
        }

        auto texturePath = directory + "/" + "textures" + "/" + baseFilename;
        auto loadedTexture = std::make_shared<Texture>(texturePath);


        if (loadedTexture) {
            loadedTexture->type = typeName;
            loadedTexture->path = pathFromAssimp;
            
            textures.push_back(loadedTexture);
            loadedTextures.push_back(loadedTexture);
        } else {
            std::cerr << "Failed to load texture for (Assimp path: [" << pathFromAssimp << "])." << std::endl;
        }
    }
    return textures;
}

std::shared_ptr<Mesh> Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> processedVertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;

        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        if (mesh->HasNormals()) {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        } else {
            vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        if (mesh->mTextureCoords[0]) { 
            vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
            vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
        } else {
            vertex.texCoords = glm::vec2(0.0f, 0.0f); 
        }
        processedVertices.push_back(vertex);
    }

    std::vector<GLuint> processedIndices;
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            processedIndices.push_back(face.mIndices[j]);
        }
    }

    GLuint diffuseTextureId = 0; // Default to no texture
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
        
        std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(aiMat, aiTextureType_DIFFUSE, "texture_diffuse");

        if (!diffuseMaps.empty() && diffuseMaps[0]) { 
            diffuseTextureId = diffuseMaps[0]->getTextureID();
        }
    }

    return std::make_shared<Mesh>(processedVertices, processedIndices, diffuseTextureId);
}
