#pragma once

#include <iostream>
#include <list>

#include "pgr.h"
#include "Game/data.h"
#include "GameObjects/GameObject.h"
#include "Rendering/ShaderProgram.h"
#include "Game/GameEvents.h"
#include "GameObjects/CameraObject.h"


class GameUtils
{
public:
    struct GameInformation
    {
        int windowWidth;
        int windowHeight;

        float cameraElevationAngle;
        float cameraAzimuthAngle;

        bool gameOver;

        float elapsedTime;
        float missileLaunchTime;
        float ufoMissileLaunchTime;
    } gameInfo;

    std::unique_ptr<ShaderProgram> mainShader;

    std::vector<std::shared_ptr<GameObject>> gameObjects;

    std::shared_ptr<CameraObject> playerCamera;

    static std::unique_ptr<GameUtils> instance;


    GameUtils();

    static void InitializeFramework();

    static void InitializeGlut(int argc, char** argv);

    void StartGame();

    static void InitializeShaders();

    static void InitializeModels();

    static void FinalizeGame();

    static void PrintGPUInfo();
};
