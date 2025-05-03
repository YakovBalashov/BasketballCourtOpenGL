#include "rendering.h"

#include <iostream>

#include "GameObjects/TestObject.h"

GLfloat testVertices[] = {
    -0.5f, 0.0f, 0.5f,
    -0.5f, 0.0f, -0.5f,
    0.5f, 0.0f, -0.5f,
    0.5f, 0.0f, 0.5f,
    0.0f, 0.8f, 0.0f,
};


GLuint testIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};


GLuint vao, vbo, ebo;

ShaderProgram* mainShader;


void initializeShaders()
{
    mainShader = new ShaderProgram("Shaders/simple.vert", "Shaders/simple.frag");
}

void cleanupShaders()
{
    delete mainShader;
}

void initializeModels()
{
    /*glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(testVertices), testVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
    TestObject::CreateMesh(testVertices, testIndices, sizeof(testVertices), sizeof(testIndices));
}

void cleanupModels()
{
    // glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &vbo);
}
