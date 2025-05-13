/**
* \file Texture.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Texture class for loading and managing textures.
 */

#pragma once
#include <string>
#include "pgr.h"

class Texture
{
public:
    std::string type;
    std::string path;

    Texture(const std::string& filePath,
            GLint wrapS = GL_REPEAT,
            GLint wrapT = GL_REPEAT,
            GLint minFilter = GL_LINEAR_MIPMAP_LINEAR,
            GLint magFilter = GL_LINEAR);

    ~Texture();

    GLuint getTextureID() const;

private:
    GLuint textureID;
};
