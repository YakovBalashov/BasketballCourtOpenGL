#pragma once

#include "pgr.h"

namespace Window
{
    constexpr int height = 750;
    constexpr int width = 750;
    constexpr auto title = "Basketball Court";
}


namespace Scene
{
    constexpr float width = 1.0f;
    constexpr float height = 1.0f;
    constexpr float depth = 1.0f;
}

namespace LightsConfig
{
    extern glm::vec3 sunColor;
    extern glm::vec3 sunDirection;
    constexpr float sunAmbientIntensity = 0.4f;
    constexpr float sunDiffuseIntensity = 0.6f;
    constexpr float sunSpecularIntensity = 1.0f;

    extern glm::vec3 pointLightColor;
    constexpr float pointLightAmbientIntensity = 0.0f;
    constexpr float pointLightDiffuseIntensity = 0.7f;
    constexpr float pointLightSpecularIntensity = 1.0f;
    constexpr float pointLightConstant = 1.0f;
    constexpr float pointLightLinear = 0.09f;
    constexpr float pointLightQuadratic = 0.032f;

    extern glm::vec3 flashLightColor;
    extern glm::vec3 flashLightDirection;
    constexpr float flashLightAmbientIntensity = 0.0f;
    constexpr float flashLightDiffuseIntensity = 0.7f;
    constexpr float flashLightSpecularIntensity = 1.0f;
    extern float flashLightCutOff;
}

namespace CameraConfig
{
    constexpr float maxElevation = 45.0f;
    constexpr float verticalSensitivity = 0.05f;
    constexpr float horizontalSensitivity = 0.05f;
    constexpr float fovy = 60.0f;
    constexpr float nearPlane = 0.1f;
    constexpr float farPlane = 100.0f;
}

namespace DebugGrid
{
    constexpr float size = 50.0f;
    constexpr float step = 5.0f;
    constexpr float yLevel = 0.1f;
}


namespace Ground
{
    constexpr float size = 0.1f;
}

namespace Player
{
    constexpr float normalSpeed = 5.0f;
    constexpr float sprintSpeed = 10.0f;
}

namespace Input
{
    constexpr unsigned char moveForward = 'w';
    constexpr unsigned char moveBackward = 's';
    constexpr unsigned char moveLeft = 'a';
    constexpr unsigned char moveRight = 'd';
    constexpr unsigned char exitGame = 27;
    constexpr unsigned char toggleFullscreen = 'f';
    constexpr unsigned char toggleFlashLight = 'e';
    constexpr unsigned char toggleDebugGrid = GLUT_KEY_F3;
    constexpr unsigned char cycleCamera = GLUT_KEY_F5;
    constexpr unsigned char sprint = GLUT_KEY_SHIFT_L;
}


