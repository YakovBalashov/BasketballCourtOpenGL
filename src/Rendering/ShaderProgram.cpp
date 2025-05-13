/**
* \file ShaderProgram.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Shader program class for managing OpenGL shaders and uniforms.
 */


#include "Rendering/ShaderProgram.h"

#include <iostream>


ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    std::vector<GLuint> shaderList;

    shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, vertexShaderFile));
    shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragmentShaderFile));

    program = pgr::createProgram(shaderList);
    modelMatrixLocation = glGetUniformLocation(program, "model");
    viewMatrixLocation = glGetUniformLocation(program, "view");
    projectionMatrixLocation = glGetUniformLocation(program, "projection");

    cameraPositionLocation = glGetUniformLocation(program, "cameraPosition");
    
    textureSamplerLocation = glGetUniformLocation(program, "textureSampler");
    textureOffsetSpeedLocation = glGetUniformLocation(program, "textureOffsetSpeed");
    textureOffsetTimeLocation = glGetUniformLocation(program, "textureOffsetTime");
    

    materialAmbientColorLocation = glGetUniformLocation(program, "material.ambient");
    materialDiffuseColorLocation = glGetUniformLocation(program, "material.diffuse");
    materialSpecularColorLocation = glGetUniformLocation(program, "material.specular");
    materialShininessLocation = glGetUniformLocation(program, "material.shininess");

    sunDirectionLocation = glGetUniformLocation(program, "sun.direction");
    sunColorLocation = glGetUniformLocation(program, "sun.color");
    sunAmbientIntensityLocation = glGetUniformLocation(program, "sun.ambientIntensity");
    sunDiffuseIntensityLocation = glGetUniformLocation(program, "sun.diffuseIntensity");
    sunSpecularIntensityLocation = glGetUniformLocation(program, "sun.specularIntensity");

    pointLightPositionLocation = glGetUniformLocation(program, "pointLight.position");
    pointLightColorLocation = glGetUniformLocation(program, "pointLight.color");
    pointLightAmbientIntensityLocation = glGetUniformLocation(program, "pointLight.ambientIntensity");
    pointLightDiffuseIntensityLocation = glGetUniformLocation(program, "pointLight.diffuseIntensity");
    pointLightSpecularIntensityLocation = glGetUniformLocation(program, "pointLight.specularIntensity");
    pointLightConstantLocation = glGetUniformLocation(program, "pointLight.constant");
    pointLightLinearLocation = glGetUniformLocation(program, "pointLight.linear");
    pointLightQuadraticLocation = glGetUniformLocation(program, "pointLight.quadratic");

    flashLightPositionLocation = glGetUniformLocation(program, "flashLight.position");
    flashLightDirectionLocation = glGetUniformLocation(program, "flashLight.direction");
    flashLightColorLocation = glGetUniformLocation(program, "flashLight.color");
    flashLightAmbientIntensityLocation = glGetUniformLocation(program, "flashLight.ambientIntensity");
    flashLightDiffuseIntensityLocation = glGetUniformLocation(program, "flashLight.diffuseIntensity");
    flashLightSpecularIntensityLocation = glGetUniformLocation(program, "flashLight.specularIntensity");
    flashLightCutOffLocation = glGetUniformLocation(program, "flashLight.cutOff");
    flashLightStateLocation = glGetUniformLocation(program, "flashLight.state");
    
    directionalLightColorLocation = glGetUniformLocation(program, "directionalLightColor");
    directionalLightPositionLocation = glGetUniformLocation(program, "directionalLightPosition");

    frameCountLocation = glGetUniformLocation(program, "frameCount");
    currentFrameLocation = glGetUniformLocation(program, "currentFrame");

    fogColorLocation = glGetUniformLocation(program, "fog.color");
    fogStartLocation = glGetUniformLocation(program, "fog.start");
    fogEndLocation = glGetUniformLocation(program, "fog.end");
    
    glEnable(GL_DEPTH_TEST);
}

ShaderProgram::~ShaderProgram()
{
    pgr::deleteProgramAndShaders(program);
}

void ShaderProgram::UseProgram() const
{
    glUseProgram(program);
}

void ShaderProgram::SetPVM(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix) const
{
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void ShaderProgram::SetTextureSampler(GLint textureID) const
{
    glUniform1i(textureSamplerLocation, textureID);
}

void ShaderProgram::SetSunParameters(const glm::vec3& direction, const glm::vec3& color, float ambientIntensity, float diffuseIntensity, float
                                     specularIntensity) const
{
    glUniform3fv(sunDirectionLocation, 1, glm::value_ptr(direction));
    glUniform3fv(sunColorLocation, 1, glm::value_ptr(color));
    glUniform1f(sunAmbientIntensityLocation, ambientIntensity);
    glUniform1f(sunDiffuseIntensityLocation, diffuseIntensity);
    glUniform1f(sunSpecularIntensityLocation, specularIntensity);
}

void ShaderProgram::SetSunColorAndIntensity(const glm::vec3& color, float ambientIntensity, float diffuseIntensity,
    float specularIntensity) const
{
    glUniform3fv(sunColorLocation, 1, glm::value_ptr(color));
    glUniform1f(sunAmbientIntensityLocation, ambientIntensity);
    glUniform1f(sunDiffuseIntensityLocation, diffuseIntensity);
    glUniform1f(sunSpecularIntensityLocation, specularIntensity);
}


void ShaderProgram::SetCameraPosition(const glm::vec3& position) const
{
    glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(position));
}

void ShaderProgram::SetMaterial(const std::shared_ptr<Material>& material) const
{
    glUniform3fv(materialAmbientColorLocation, 1, glm::value_ptr(material->ambientColor));
    glUniform3fv(materialDiffuseColorLocation, 1, glm::value_ptr(material->diffuseColor));
    glUniform3fv(materialSpecularColorLocation, 1, glm::value_ptr(material->specularColor));
    glUniform1f(materialShininessLocation, material->shininess);
}

void ShaderProgram::SetPointLightParameters(const glm::vec3& position, const glm::vec3& color, float ambientIntensity,
    float diffuseIntensity, float specularIntensity, float constant, float linear, float quadratic) const
{
    glUniform3fv(pointLightPositionLocation, 1, glm::value_ptr(position));
    glUniform3fv(pointLightColorLocation, 1, glm::value_ptr(color));
    
    glUniform1f(pointLightAmbientIntensityLocation, ambientIntensity);
    glUniform1f(pointLightDiffuseIntensityLocation, diffuseIntensity);
    glUniform1f(pointLightSpecularIntensityLocation, specularIntensity);
    
    glUniform1f(pointLightConstantLocation, constant);
    glUniform1f(pointLightLinearLocation, linear);
    glUniform1f(pointLightQuadraticLocation, quadratic);
}

void ShaderProgram::SetPointLightColor(const glm::vec3& color) const
{
    glUniform3fv(pointLightColorLocation, 1, glm::value_ptr(color));
}

void ShaderProgram::SetFlashLightParameters(const glm::vec3& position, const glm::vec3& direction,
                                            const glm::vec3& color, float ambientIntensity, float diffuseIntensity, float specularIntensity, float cutOff) const
{
    glUniform3fv(flashLightPositionLocation, 1, glm::value_ptr(position));
    glUniform3fv(flashLightDirectionLocation, 1, glm::value_ptr(direction));
    
    glUniform3fv(flashLightColorLocation, 1, glm::value_ptr(color));
    
    glUniform1f(flashLightAmbientIntensityLocation, ambientIntensity);
    glUniform1f(flashLightDiffuseIntensityLocation, diffuseIntensity);
    glUniform1f(flashLightSpecularIntensityLocation, specularIntensity);
    
    glUniform1f(flashLightCutOffLocation, cutOff);
}



void ShaderProgram::SetFlashLightPositionAndDirection(const glm::vec3& position, const glm::vec3& direction) const
{
    glUniform3fv(flashLightPositionLocation, 1, glm::value_ptr(position));
    glUniform3fv(flashLightDirectionLocation, 1, glm::value_ptr(direction));
}

void ShaderProgram::SetFlashLightState(bool state) const
{
    std::cout << "Flashlight state: " << state << std::endl;
    glUniform1i(flashLightStateLocation, 1);
}

void ShaderProgram::SetTime(float time) const
{
    glUniform1f(textureOffsetTimeLocation, time);
}

void ShaderProgram::SetTextureOffsetSpeed(const glm::vec2& speed) const
{
    glUniform2fv(textureOffsetSpeedLocation, 1, glm::value_ptr(speed));
}

void ShaderProgram::SetFrameCount(int frameCount) const
{
    glUniform1i(frameCountLocation, frameCount);
}

void ShaderProgram::SetCurrentFrame(int currentFrame) const
{
    glUniform1i(currentFrameLocation, currentFrame);
}

void ShaderProgram::SetFogParameters(const glm::vec3& fogColor, float fogStart, float fogEnd) const
{
    glUniform3fv(fogColorLocation, 1, glm::value_ptr(fogColor));
    glUniform1f(fogStartLocation, fogStart);
    glUniform1f(fogEndLocation, fogEnd);
}



