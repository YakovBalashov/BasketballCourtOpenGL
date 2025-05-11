#pragma once
#include <GameObjects/RenderableObject.h>
#include <Game/paths.h>
#include <Game/config.h>

constexpr auto skyboxFaceCount = 6;

struct SunParameters {
    glm::vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    SunParameters(const glm::vec3& color = {1.0f, 1.0f, 1.0f}, float ambientIntensity = 0.4f,
                  float diffuseIntensity = 0.6f, float specularIntensity = 1.0f)
        : color(color), ambientIntensity(ambientIntensity), diffuseIntensity(diffuseIntensity),
          specularIntensity(specularIntensity) {}
};

struct FogParameters
{
    glm::vec3 color;
    float start;
    float end;

    FogParameters(const glm::vec3& color = {0.5f, 0.5f, 0.5f}, float start = 0.0f, float end = 1.0f)
        : color(color), start(start), end(end) {}
};

class Skybox : public RenderableObject
{
public:
    void LoadTexturesFromFolder(const std::string& folderPath);
    
    void SetupMesh();

    void LoadTextures();
    
    Skybox(const std::shared_ptr<ShaderProgram>& shaderProgram);

    void RenderObject(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

    void CycleSkybox();

private:
    GLuint skyboxVAO, skyboxVBO;
    
    std::vector<GLuint> textureIDs;
    
    std::vector<std::string> skyboxFolders = {
        TexturePaths::blueSkybox,
        TexturePaths::silentHillSkybox,
    };

    std::vector<SunParameters> sunParameters = {
        {LightsConfig::sunColor, LightsConfig::sunAmbientIntensity, LightsConfig::sunDiffuseIntensity, LightsConfig::sunSpecularIntensity},
        {LightsConfig::sunColor, LightsConfig::silentHillAmbientIntensity, LightsConfig::silentHillDiffuseIntensity, LightsConfig::silentHillSpecularIntensity},
    };

    std::vector<FogParameters> fogParameters = {
    {Fog::normalColor, Fog::normalStart, Fog::normalEnd},
        {Fog::normalColor, Fog::silentHillStart, Fog::silentHillEnd},
    };
    
    int currentSkybox = 0;
};
