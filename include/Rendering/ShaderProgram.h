#pragma once
#include "Material.h"
#include "pgr.h"

class ShaderProgram
{
public:
    ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

    ~ShaderProgram();

    void UseProgram() const;

    void SetPVM(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix) const;

    void SetTextureSampler(GLint textureID) const;

    void SetAmbientLight(const glm::vec3& color, float intensity) const;

    void SetDirectionalLightColor(const glm::vec3& color) const;

    void SetDirectionalLightPosition(const glm::vec3& position) const;

    void SetCameraPosition(const glm::vec3& position) const;
    
    void SetMaterial(const std::shared_ptr<Material>& material) const;

    ShaderProgram(const ShaderProgram&) = delete;

    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&&) = delete;

    ShaderProgram& operator=(ShaderProgram&&) = delete;

private:
    GLuint program;

    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;

    GLint cameraPositionLocation;

    GLint textureSamplerLocation;

    GLint materialAmbientColorLocation;
    GLint materialDiffuseColorLocation;
    GLint materialSpecularColorLocation;
    GLint materialShininessLocation;

    GLint ambientLightColorLocation;
    GLint ambientLightIntensityLocation;
    
    GLint directionalLightColorLocation;
    GLint directionalLightPositionLocation;
};
