/**
* \file paths.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Paths for the game assets.
 */

#pragma once

namespace TexturePaths
{
    constexpr auto blueSkybox = "assets/textures/skybox/blue";
    constexpr auto silentHillSkybox = "assets/textures/skybox/gray";
    constexpr auto red = "assets/textures/red.png";
    constexpr auto green = "assets/textures/green.png";
    constexpr auto blue = "assets/textures/blue.png";
    constexpr auto white = "assets/textures/white.png";
    constexpr auto gray = "assets/textures/gray.png";
    constexpr auto logo = "assets/textures/logo.JPG";
    constexpr auto portal = "assets/textures/portal.png";
    constexpr auto counter = "assets/textures/counter.png";
    constexpr auto buttonBG = "assets/textures/button_bg.png";
}

namespace ModelPaths
{
    constexpr auto courtModel = "assets/models/court/Court.fbx";
    constexpr auto basketballModel = "assets/models/basketball_common/basketballball.obj";
    constexpr auto basketballFbx = "assets/models/BasketballFBX/Basket_Ball.fbx";
    constexpr auto basketballB = "assets/models/basketball_b/ball_b.obj";
    constexpr auto droneS = "assets/models/drone/SciFiDroid.obj";
    constexpr auto portalCube = "assets/models/cube/portal.obj";
    constexpr auto streetLight = "assets/models/StreetLight/Street_Lamp_1.obj";
    constexpr auto bench = "assets/models/bech/bech.fbx";
}

namespace ShaderPaths
{
    constexpr auto simpleVertexShader = "shaders/simple.vert";
    constexpr auto simpleFragmentShader = "shaders/simple.frag";
    constexpr auto skyboxVertexShader = "shaders/skybox.vert";
    constexpr auto skyboxFragmentShader = "shaders/skybox.frag";
    constexpr auto colorVertexShader = "shaders/color.vert";
    constexpr auto colorFragmentShader = "shaders/color.frag";
    constexpr auto animatedVertexShader = "shaders/animated.vert";
    constexpr auto animatedFragmentShader = "shaders/animated.frag";
}

