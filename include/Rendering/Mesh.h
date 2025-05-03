#pragma once

#include "pgr.h"

class Mesh
{
public:
    Mesh(const GLfloat* vertices, int vertexCount, const GLuint* indices, int indexCount);

    ~Mesh();

    void Render() const;

private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    int vertexCount;
    int indexCount;
};
