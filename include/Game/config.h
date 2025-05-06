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

namespace Camera
{
    constexpr float maxElevation = 45.0f;
    constexpr float verticalSensitivity = 0.05f;
    constexpr float horizontalSensitivity = 0.05f;
    constexpr float fovy = 60.0f;
    constexpr float nearPlane = 0.1f;
    constexpr float farPlane = 50.0f;
}

namespace Ground
{
    constexpr float size = 50.0f;
}

namespace Player
{
    constexpr float normalSpeed = 5.0f;
    constexpr float sprintSpeed = 8.0f;
}

namespace Input
{
    constexpr unsigned char moveForward = 'w';
    constexpr unsigned char moveBackward = 's';
    constexpr unsigned char moveLeft = 'a';
    constexpr unsigned char moveRight = 'd';
    constexpr unsigned char exitGame = 27;
    constexpr unsigned char toggleFullscreen = 'f';
    constexpr unsigned char sprint = GLUT_KEY_SHIFT_L;
}
