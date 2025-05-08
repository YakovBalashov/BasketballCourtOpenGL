#pragma once
#include "Camera.h"
#include "ModelObject.h"

class Drone : public ModelObject
{
public:
    Drone(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, const std::shared_ptr<Model>& model,
          const std::shared_ptr<ShaderProgram>& shaderProgram)
        : ModelObject(position, rotation, scale, model, shaderProgram)
    {
    }

    void Update() override;
};
