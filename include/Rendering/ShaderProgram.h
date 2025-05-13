/**
* \file ShaderProgram.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Shader program class for managing OpenGL shaders and uniforms.
 */

#pragma once
#include "Material.h"
#include "pgr.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Camera.h"

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

    void SetSunColorAndIntensity(const glm::vec3& color, float ambientIntensity, float diffuseIntensity, float specularIntensity) const;

    void SetCameraPosition(const glm::vec3& position) const;

    void SetMaterial(const std::shared_ptr<Material>& material) const;
    
    void SetPointLightParameters(const glm::vec3& position, const glm::vec3& color, float ambientIntensity, float diffuseIntensity, float specularIntensity,
                               float constant, float linear, float quadratic) const;

    void SetPointLightColor(const glm::vec3& color) const;

    void SetFlashLightParameters(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, float ambientIntensity,
                               float diffuseIntensity, float specularIntensity, float cutOff) const;

    void SetFlashLightPositionAndDirection(const glm::vec3& position, const glm::vec3& direction) const;

    void SetFlashLightState(bool state) const;

    void SetTime(float time) const;
    
    void SetTextureOffsetSpeed(const glm::vec2& speed) const;

    void SetFrameCount(int frameCount) const;

    void SetCurrentFrame(int currentFrame) const;

    void SetFogParameters(const glm::vec3& fogColor, float fogStart, float fogEnd) const;
    
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
    GLint textureOffsetSpeedLocation;
    GLint textureOffsetTimeLocation;

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

    GLint frameCountLocation;
    GLint currentFrameLocation;

    GLint fogColorLocation;
    GLint fogStartLocation;
    GLint fogEndLocation;
};
