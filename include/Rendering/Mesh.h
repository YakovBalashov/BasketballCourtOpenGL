#pragma once

#include "pgr.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh
{
public:
    Mesh(const GLfloat* vertices, const GLuint* indices, int vertexCount, int indexCount);

    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint textureID);
    
    ~Mesh();

    virtual void Render();

protected:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    int vertexCount;
    int indexCount;
    GLuint textureID;
};
