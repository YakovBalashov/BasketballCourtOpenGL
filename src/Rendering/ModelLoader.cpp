#include <iostream>
#include <Rendering/ModelLoader.h>

std::shared_ptr<Mesh> ModelLoader::LoadFromFile(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error("Failed to load model from file " + path);

    if (scene->mNumMeshes != 1)
        throw std::runtime_error("Model from file " + path + " contains more than one mesh");

    std::cout << "loading model from file " << path << std::endl;
    return nullptr;
}
