#pragma once
#include "Mesh.h"

class DebugMesh : public Mesh
{
public:
    DebugMesh(const GLfloat* vertices, const GLuint* indices, int vertexCount, int indexCount)
        : Mesh(vertices, indices, vertexCount, indexCount)
    {
    }

    DebugMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLuint textureID)
        : Mesh(vertices, indices, textureID)
    {
    }

    void Render() override;
};
