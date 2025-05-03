#pragma once
#include "pgr.h"
#include "Rendering/ShaderProgram.h"

extern GLfloat testVertices[];
extern GLuint testIndices[];
extern GLuint vao, vbo, ebo;

extern ShaderProgram* mainShader;

void initializeShaders();

void cleanupShaders();

void initializeModels();

void cleanupModels();

