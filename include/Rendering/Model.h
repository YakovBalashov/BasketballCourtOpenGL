#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Mesh.h"


class Model
{
public:
    explicit Model(const std::string& path);

    void Render() const;

private:
    std::vector<std::shared_ptr<Mesh>> meshes;
    void ProcessNode(const aiNode* node, const aiScene* scene);
    static std::shared_ptr<Mesh> ProcessMesh(const aiMesh* mesh);
};
