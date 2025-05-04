#pragma once

#include <iostream>
#include <list>

#include "pgr.h"
#include "Game/data.h"
#include "GameObjects/GameObject.h"
#include "Rendering/ShaderProgram.h"
#include "Game/GameEvents.h"


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
        bool keyMap[KEYS_COUNT];

        float elapsedTime;
        float missileLaunchTime;
        float ufoMissileLaunchTime;
    } gameInfo;

    std::unique_ptr<ShaderProgram> mainShader;

    std::list<GameObject*> gameObjects;

    static std::unique_ptr<GameUtils> instance;


    GameUtils();

    static void InitializeFramework();

    static void SetupApp(int argc, char** argv);

    void StartApp();

    static void FinalizeApplication();

    static void PrintGPUInfo();
    
    static void InitializeShaders();

    static void InitializeModels();
};
