#pragma once
#include <GameObjects/RenderableObject.h>
#include <Game/paths.h>

constexpr auto skyboxFaceCount = 6;

class Skybox : public RenderableObject
{
public:
    Skybox(const std::shared_ptr<ShaderProgram>& shaderProgram);

    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
    GLuint textureID;
};
