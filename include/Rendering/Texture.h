#pragma once
#include <string>
#include "pgr.h"

class Texture
{
public:
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
