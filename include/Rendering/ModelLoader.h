#pragma once
#include <memory>

#include <Rendering/Mesh.h>

class ModelLoader
{
public:
    static std::shared_ptr<Mesh> LoadFromFile(const std::string& path);
};
