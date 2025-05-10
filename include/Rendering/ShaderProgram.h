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

    void SetSunParameters(const glm::vec3& direction, const glm::vec3& color, float ambientIntensity, float diffuseIntensity, float
                          specularIntensity) const;

    void SetCameraPosition(const glm::vec3& position) const;

    void SetMaterial(const std::shared_ptr<Material>& material) const;
    
    void SetPointLightParameters(const glm::vec3& position, const glm::vec3& color, float ambientIntensity, float diffuseIntensity, float specularIntensity,
                               float constant, float linear, float quadratic) const;

    void SetFlashLightParameters(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, float ambientIntensity,
                               float diffuseIntensity, float specularIntensity, float cutOff) const;

    void SetFlashLightPositionAndDirection(const glm::vec3& position, const glm::vec3& direction) const;

    void SetFlashLightState(bool state) const; 

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

    GLint sunDirectionLocation;
    GLint sunColorLocation;
    GLint sunAmbientIntensityLocation;
    GLint sunDiffuseIntensityLocation;
    GLint sunSpecularIntensityLocation;

    GLint pointLightPositionLocation;
    GLint pointLightColorLocation;
    GLint pointLightAmbientIntensityLocation;
    GLint pointLightDiffuseIntensityLocation;
    GLint pointLightSpecularIntensityLocation;
    GLint pointLightConstantLocation;
    GLint pointLightLinearLocation;
    GLint pointLightQuadraticLocation;

    GLint flashLightPositionLocation;
    GLint flashLightDirectionLocation;
    GLint flashLightColorLocation;
    GLint flashLightAmbientIntensityLocation;
    GLint flashLightDiffuseIntensityLocation;
    GLint flashLightSpecularIntensityLocation;
    GLint flashLightCutOffLocation;
    GLint flashLightStateLocation;
    
    GLint directionalLightColorLocation;
    GLint directionalLightPositionLocation;
};
