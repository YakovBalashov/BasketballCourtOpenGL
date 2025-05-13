/**
* \file Texture.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Texture class for loading and managing textures.
 */


#include "../../include/Rendering/Texture.h"

Texture::Texture(const std::string& filePath, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter)
{
    textureID = pgr::createTexture(filePath);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

GLuint Texture::getTextureID() const
{
    return textureID;
}
