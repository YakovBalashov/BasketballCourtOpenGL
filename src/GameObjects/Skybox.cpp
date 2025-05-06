#include <GameObjects/Skybox.h>



Skybox::Skybox(const std::shared_ptr<ShaderProgram>& shaderProgram) 
    : RenderableObject(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), shaderProgram)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    for (int i = 0; i < skyboxFaceCount; ++i)
    {
        std::string texturePath = std::string(TexturePaths::blueSkybox) + "/" + std::to_string(i) + ".png";
        pgr::loadTexImage2D(texturePath, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
    }
}


void Skybox::RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    
}
