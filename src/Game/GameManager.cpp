#include "Game/GameManager.h"

#include "Game/meshes.h"
#include "Game/PlayerInput.h"
#include "GameObjects/Drone.h"
#include "GameObjects/Camera.h"
#include "GameObjects/ModelObject.h"
#include "GameObjects/PointLight.h"
#include "GameObjects/Skybox.h"
#include "GameObjects/TestObject.h"
#include "Rendering/DebugMesh.h"
#include "Rendering/Texture.h"
#include "Rendering/Material.h"

std::unique_ptr<GameManager> GameManager::instance = nullptr;

GameManager::GameManager()
{
    if (instance) return;
    instance = std::unique_ptr<GameManager>(this);
}

void GameManager::InitializeGlut(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

    glutInitWindowSize(Window::width, Window::height);
    glutCreateWindow(Window::title);
    glutFullScreen();

    glutDisplayFunc(GameEvents::OnRenderDisplay);
    glutReshapeFunc(GameEvents::OnReshapeWindow);
    glutKeyboardFunc(PlayerInput::OnKeyPress);
    glutKeyboardUpFunc(PlayerInput::OnKeRelease);
    glutSpecialFunc(PlayerInput::OnSpecialKeyPress);
    glutSpecialUpFunc(PlayerInput::OnSpecialKeyRelease);
    glutPassiveMotionFunc(GameEvents::OnPassiveMouseMotion);
    glutMouseFunc(GameEvents::OnMouseAction);
    glutSetCursor(GLUT_CURSOR_NONE);

    glutTimerFunc(33, GameEvents::OnTimer, 0);
    glutWMCloseFunc(FinalizeGame);
}

void GameManager::SetupCameras()
{
    playerCamera = std::make_shared<PlayerCamera>(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    cameras.push_back(playerCamera);
    gameObjects.push_back(playerCamera);

    auto staticCameraA = std::make_shared<Camera>(glm::vec3(7.0f, 50.0f, 0.0f), glm::vec3(315.0f, 0.0f, 0.0f),
                                                  glm::vec3(1.0f));
    cameras.push_back(staticCameraA);
    gameObjects.push_back(staticCameraA);

    auto staticCameraB = std::make_shared<Camera>(glm::vec3(0.0f, 2.0f, -5.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    cameras.push_back(staticCameraB);
    gameObjects.push_back(staticCameraB);

    auto droneModel = std::make_shared<Model>(ModelPaths::droneS);
    auto drone = std::make_shared<Drone>(glm::vec3(1.0f), droneModel, mainShader, std::make_shared<Material>(),
                                         glm::vec3(0.0f, 4.0f, 0.0f), 10.0f, 10.0f);
    auto droneCamera = std::make_shared<Camera>(glm::vec3(0.0f, -0.2f, 0.7f), glm::vec3(0.0f), glm::vec3(1.0f));
    drone->AddChild(droneCamera);
    gameObjects.push_back(drone);
    // gameObjects.push_back(droneCamera);
    cameras.push_back(droneCamera);

    currentCamera = cameras[currentCameraIndex];
}

void GameManager::InitializeFramework()
{
    if (pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) return;
    pgr::dieWithError("PGR Framework Initialization Failed");
}

void GameManager::StartGame()
{
    glutWarpPointer(GameManager::instance->gameInfo.windowWidth / 2, GameManager::instance->gameInfo.windowHeight / 2);

    // initialize random seed
    // srand((unsigned int)time(NULL));

    // initialize OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    InitializeShaders();
    InitializeModels();


    SetupCameras();

    auto concreteTexture = std::make_shared<Texture>("assets/textures/concrete_a.jpg");
    auto redTexture = std::make_shared<Texture>(TexturePaths::red);
    auto whiteTexture = std::make_shared<Texture>(TexturePaths::white);

    auto defaultMaterial = std::make_shared<Material>();
    auto shinyMaterial = std::make_shared<Material>(glm::vec3(1.0f), glm::vec3(0.7f), glm::vec3(1.0f), 32.0f);
    auto diffuseMaterial = std::make_shared<Material>(glm::vec3(0.5f), glm::vec3(0.7f), glm::vec3(0.0f), 32.0f);

    /*
    auto courtModel = std::make_shared<Model>(ModelPaths::courtModel);
    auto court = std::make_shared<ModelObject>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f),
                                               courtModel, mainShader, defaultMaterial);
    gameObjects.push_back(court);
    */
    
    auto streetLampModel = std::make_shared<Model>(ModelPaths::streetLight);
    auto streetLamp = std::make_shared<ModelObject>(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f),
                                                    streetLampModel, mainShader, defaultMaterial);
    gameObjects.push_back(streetLamp);

    auto cubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices,
                                           redTexture->getTextureID());
    auto lightCubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices,
                                                whiteTexture->getTextureID());
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(2.0f, 0.5f, -35.8f), glm::vec3(0.0f), glm::vec3(1.0f),
                                                       cubeMesh, mainShader, shinyMaterial));
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(2.0f, 0.8f, -34.0f), glm::vec3(0.0f), glm::vec3(1.5f),
                                                       cubeMesh, mainShader, defaultMaterial));
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(2.1f, 0.6f, -32.2f), glm::vec3(0.0f), glm::vec3(1.2f),
                                                       cubeMesh, mainShader, diffuseMaterial));

    auto pointLight = std::make_shared<PointLight>(glm::vec3(3.5f, 0.5f, -34.2f), glm::vec3(0.0f), glm::vec3(0.2f),
                                                   lightCubeMesh, colorShader, shinyMaterial);

    interactableObjects.push_back(pointLight);
    
    gameObjects.push_back(pointLight);

    GameUtils::GenerateGrid(DebugGrid::size, DebugGrid::step);

    skybox = std::make_shared<Skybox>(skyboxShader);

    mainShader->UseProgram();
    mainShader->SetSunParameters(LightsConfig::sunDirection, LightsConfig::sunColor,
                                 LightsConfig::sunAmbientIntensity, LightsConfig::sunDiffuseIntensity,
                                 LightsConfig::sunSpecularIntensity);
    mainShader->SetPointLightParameters(pointLight->GetPosition(), LightsConfig::pointLightColor,
                                        LightsConfig::pointLightAmbientIntensity,
                                        LightsConfig::pointLightDiffuseIntensity,
                                        LightsConfig::pointLightSpecularIntensity, LightsConfig::pointLightConstant,
                                        LightsConfig::pointLightLinear, LightsConfig::pointLightQuadratic);
    mainShader->SetFlashLightParameters(glm::vec3(0.0f, 3.0f, 0.0f), LightsConfig::flashLightDirection,
                                        LightsConfig::flashLightColor,
                                        LightsConfig::flashLightAmbientIntensity,
                                        LightsConfig::flashLightDiffuseIntensity,
                                        LightsConfig::flashLightSpecularIntensity, LightsConfig::flashLightCutOff);

    glutMainLoop();
}

void GameManager::ChangeActiveCamera(int direction)
{
    currentCameraIndex = static_cast<int>(GameUtils::Repeat(
        static_cast<float>(currentCameraIndex) + static_cast<float>(direction), static_cast<float>(cameras.size())));
    currentCamera = cameras[currentCameraIndex];
}

void GameManager::InitializeShaders()
{
    instance->mainShader = std::make_shared<ShaderProgram>(ShaderPaths::simpleVertexShader,
                                                           ShaderPaths::simpleFragmentShader);
    instance->skyboxShader = std::make_shared<ShaderProgram>(ShaderPaths::skyboxVertexShader,
                                                             ShaderPaths::skyboxFragmentShader);
    instance->colorShader = std::make_shared<ShaderProgram>(ShaderPaths::colorVertexShader,
                                                            ShaderPaths::colorFragmentShader);
}

void GameManager::InitializeModels()
{
    // TestObject::CreateMesh(testVertices, testIndices, sizeof(testVertices), sizeof(testIndices));
}

void GameManager::FinalizeGame()
{
    exit(0);
}

void GameManager::PrintGPUInfo()
{
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);

    std::cout << "GPU Vendor:   " << vendor << '\n';
    std::cout << "GPU Renderer: " << renderer << '\n';
    std::cout << "OpenGL Version: " << version << '\n';
}
