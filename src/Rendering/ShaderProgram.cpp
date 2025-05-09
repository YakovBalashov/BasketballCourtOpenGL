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

    materialAmbientColorLocation = glGetUniformLocation(program, "material.ambient");
    materialDiffuseColorLocation = glGetUniformLocation(program, "material.diffuse");
    materialSpecularColorLocation = glGetUniformLocation(program, "material.specular");
    materialShininessLocation = glGetUniformLocation(program, "material.shininess");

    ambientLightColorLocation = glGetUniformLocation(program, "ambientLightColor");

    directionalLightColorLocation = glGetUniformLocation(program, "directionalLightColor");
    directionalLightPositionLocation = glGetUniformLocation(program, "directionalLightPosition");
    
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

void ShaderProgram::SetAmbientLight(const glm::vec3& color, float intensity) const
{
    glUniform3fv(ambientLightColorLocation, 1, glm::value_ptr(color));
}

void ShaderProgram::SetDirectionalLightColor(const glm::vec3& color) const
{
    glUniform3fv(directionalLightColorLocation, 1, glm::value_ptr(color));
}

void ShaderProgram::SetDirectionalLightPosition(const glm::vec3& position) const
{
    glUniform3fv(directionalLightPositionLocation, 1, glm::value_ptr(position));
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




