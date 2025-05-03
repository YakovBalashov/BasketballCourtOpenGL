#pragma once
#include "pgr.h"

class ShaderProgram
{
public:
    ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

    ~ShaderProgram();
    
    void UseProgram() const;
    void SetPVM(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, const glm::mat4& modelMatrix) const;

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;
    ShaderProgram& operator=(ShaderProgram&&) = delete;
private:
    GLuint program;

    GLint modelMatrixLocation;
    GLint viewMatrixLocation;
    GLint projectionMatrixLocation;
};
