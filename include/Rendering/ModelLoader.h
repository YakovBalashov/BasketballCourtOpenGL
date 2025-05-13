/**
* \file ModelLoader.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief ModelLoader class for loading 3D models from files.
 */

#pragma once
#include <memory>

#include <Rendering/Mesh.h>

class ModelLoader
{
public:
    static std::shared_ptr<Mesh> LoadFromFile(const std::string& path);
};
