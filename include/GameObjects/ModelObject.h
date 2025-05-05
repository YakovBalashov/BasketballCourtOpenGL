#pragma once

#include <GameObjects/RenderableObject.h>
#include <Rendering/Model.h>

class ModelObject : public RenderableObject
{
public:
    explicit ModelObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<Model> model) 
        : RenderableObject(position, rotation, scale), model(std::move(model)) {}

    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
    std::shared_ptr<Model> model;
};
