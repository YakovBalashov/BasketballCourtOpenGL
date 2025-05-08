#pragma once

#include <iostream>
#include <list>

#include "pgr.h"
#include "Game/config.h"
#include "GameObjects/GameObject.h"
#include "Rendering/ShaderProgram.h"
#include "Game/GameEvents.h"
#include "GameObjects/PlayerCamera.h"
#include "GameObjects/Skybox.h"
#include "Rendering/vertices.h"


class GameManager
{
public:
    struct GameInformation
    {
        int windowWidth;
        int windowHeight;

        float cameraElevationAngle;
        float cameraAzimuthAngle;

        bool gameOver;

        float currentTime;
        float deltaTime;
    } gameInfo;

    std::shared_ptr<ShaderProgram> mainShader;

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    
    std::shared_ptr<PlayerCamera> currentCamera;

    std::shared_ptr<Skybox> skybox;
    
    static std::unique_ptr<GameManager> instance;


    GameManager();

    static void InitializeFramework();

    static void InitializeGlut(int argc, char** argv);

    void StartGame();

    static void InitializeShaders();

    static void InitializeModels();

    static void FinalizeGame();

    static void PrintGPUInfo();

    void GenerateDebugGreed(); 

private:
    std::shared_ptr<ShaderProgram> skyboxShader;

    
};
