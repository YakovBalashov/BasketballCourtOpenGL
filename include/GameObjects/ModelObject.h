/**
* \file ModelObject.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief ModelObject class that represents a 3D object with a model and material.
 */

#pragma once

#include <GameObjects/RenderableObject.h>
#include <Rendering/Model.h>

class ModelObject : public RenderableObject
{
public:
    explicit ModelObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::shared_ptr<Model>& model,
                         const std::shared_ptr<ShaderProgram>& shaderProgram, const std::shared_ptr<Material>& material)
        : RenderableObject(position, rotation, scale, shaderProgram), model(model), material(material)
    {
    }

    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Material> material;
};
