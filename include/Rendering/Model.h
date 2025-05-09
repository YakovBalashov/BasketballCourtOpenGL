#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Texture.h"


class Model
{
public:
    explicit Model(const std::string& path);

    void Render() const;

private:
    std::vector<std::shared_ptr<Mesh>> meshes;

    std::string directory;
    std::vector<std::shared_ptr<Texture>> loadedTextures;
    void ProcessNode(const aiNode* node, const aiScene* scene);

    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* material, aiTextureType type,
                                                               const char* typeName);

    std::shared_ptr<Mesh> ProcessMesh(const aiMesh* mesh, const aiScene* scene);
};
