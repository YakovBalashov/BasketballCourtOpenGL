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


