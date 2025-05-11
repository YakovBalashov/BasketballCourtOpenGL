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


class GameManager
{
public:
    struct GameInformation
    {
        int windowWidth;
        int windowHeight;
        
        float currentTime;
        float deltaTime;
        
        bool isPickingMode = false;
    } gameInfo;

    std::shared_ptr<ShaderProgram> mainShader;
    std::shared_ptr<ShaderProgram> colorShader;
    std::shared_ptr<ShaderProgram> animatedShader;

    std::vector<std::shared_ptr<GameObject>> gameObjects;

    std::vector<std::shared_ptr<GameObject>> interactableObjects;
    
    std::vector<std::shared_ptr<Camera>> cameras;
    std::shared_ptr<Camera> currentCamera;
    int currentCameraIndex = 0;
    std::shared_ptr<PlayerCamera> playerCamera;

    std::shared_ptr<Skybox> skybox;

    static std::unique_ptr<GameManager> instance;


    GameManager();

    static void InitializeFramework();

    static void InitializeGlut(int argc, char** argv);

    void SetupCameras();

    void StartGame();

    void ChangeActiveCamera(int direction=1);

    static void InitializeShaders();

    static void InitializeModels();

    static void FinalizeGame();

    static void PrintGPUInfo();


private:
    std::shared_ptr<ShaderProgram> skyboxShader;
};
