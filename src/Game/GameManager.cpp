#include "Game/GameManager.h"

#include "Game/meshes.h"
#include "Game/PlayerInput.h"
#include "GameObjects/BasketballObject.h"
#include "GameObjects/Drone.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Counter.h"
#include "GameObjects/CourtLogo.h"
#include "GameObjects/EnvironmentSwitch.h"
#include "GameObjects/ModelObject.h"
#include "GameObjects/PointLight.h"
#include "GameObjects/Skybox.h"
#include "GameObjects/SunNode.h"
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

    auto birdsViewCamera = std::make_shared<Camera>(glm::vec3(7.0f, 48.0f, 0.55f), glm::vec3(270.0f, 0.0f, 0.0f), glm::vec3(1.0f));
    cameras.push_back(birdsViewCamera);

    auto bucketCamera = std::make_shared<Camera>(glm::vec3(18.5f, 4.0f, 0.55f), glm::vec3(290.0f, -90.0f, 0.0f), glm::vec3(1.0f));
    cameras.push_back(bucketCamera);

    auto spectatorCamera = std::make_shared<Camera>(glm::vec3(7.0f, 15.0f, -20.0f), glm::vec3(210.0f, 180.0f, 0.0f), glm::vec3(1.0f));
    cameras.push_back(spectatorCamera);
    // gameObjects.push_back(staticCameraB);

    auto droneModel = std::make_shared<Model>(ModelPaths::droneS);
    auto drone = std::make_shared<Drone>(glm::vec3(1.0f), droneModel, mainShader, std::make_shared<Material>(),
                                         glm::vec3(7.0f, 5.0f, 0.55f), 10.0f, 10.0f);
    auto droneCamera = std::make_shared<Camera>(glm::vec3(0.0f, -0.2f, 0.7f), glm::vec3(0.0f), glm::vec3(1.0f));
    drone->AddChild(droneCamera);
    gameObjects.push_back(drone);
    cameras.push_back(droneCamera);

    currentCamera = cameras[currentCameraIndex];
}

void GameManager::InitializeFramework()
{
    if (pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) return;
    pgr::dieWithError("PGR Framework Initialization Failed");
}

void GameManager::SetLightParameters(std::shared_ptr<PointLight> pointLight, std::shared_ptr<GameObject> SpotLight)
{
    mainShader->UseProgram();
    mainShader->SetSunParameters(LightsConfig::sunDirection, LightsConfig::sunColor,
                                 LightsConfig::sunAmbientIntensity, LightsConfig::sunDiffuseIntensity,
                                 LightsConfig::sunSpecularIntensity);
    mainShader->SetPointLightParameters(pointLight->GetPosition(), LightsConfig::pointLightColor,
                                        LightsConfig::pointLightAmbientIntensity,
                                        LightsConfig::pointLightDiffuseIntensity,
                                        LightsConfig::pointLightSpecularIntensity, LightsConfig::pointLightConstant,
                                        LightsConfig::pointLightLinear, LightsConfig::pointLightQuadratic);
    mainShader->SetFlashLightParameters(SpotLight->GetPosition() + glm::vec3(0.0f, 3.0f, 0.0f), LightsConfig::flashLightDirection,
                                        LightsConfig::flashLightColor,
                                        LightsConfig::flashLightAmbientIntensity,
                                        LightsConfig::flashLightDiffuseIntensity,
                                        LightsConfig::flashLightSpecularIntensity, LightsConfig::flashLightCutOff);

    mainShader->SetFogParameters(Fog::normalColor, Fog::normalStart, Fog::normalEnd);
}

void GameManager::StartGame()
{
    glutWarpPointer(instance->gameInfo.windowWidth / 2, instance->gameInfo.windowHeight / 2);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    InitializeShaders();
    InitializeModels();

    SetupCameras();

    // Textures
    auto redTexture = std::make_shared<Texture>(TexturePaths::red);
    auto greenTexture = std::make_shared<Texture>(TexturePaths::green);
    auto blueTexture = std::make_shared<Texture>(TexturePaths::blue);
    auto grayTexture = std::make_shared<Texture>(TexturePaths::gray);
    auto whiteTexture = std::make_shared<Texture>(TexturePaths::white);
    auto portalTexture = std::make_shared<Texture>(TexturePaths::portal);
    auto logoTexture = std::make_shared<Texture>(TexturePaths::logo);
    auto counterTexture = std::make_shared<Texture>(TexturePaths::counter);
    auto buttonBGTexture = std::make_shared<Texture>(TexturePaths::buttonBG);
    

    // Meshes
    auto logoMesh = std::make_shared<Mesh>(MeshVertices::squareVertices, MeshVertices::squareIndices, logoTexture->getTextureID());
    auto counterMesh = std::make_shared<Mesh>(MeshVertices::counterVertices, MeshVertices::squareIndices, counterTexture->getTextureID());
    auto buttonBGMesh = std::make_shared<Mesh>(MeshVertices::squareVertices, MeshVertices::squareIndices, buttonBGTexture->getTextureID());
    auto redCubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices, redTexture->getTextureID());
    auto greenCubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices, greenTexture->getTextureID());
    auto blueCubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices, blueTexture->getTextureID());
    auto grayCubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices, grayTexture->getTextureID());
    auto lightCubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices, whiteTexture->getTextureID());

    // Materials
    auto defaultMaterial = std::make_shared<Material>();
    auto shinyMaterial = std::make_shared<Material>(glm::vec3(1.0f), glm::vec3(0.7f), glm::vec3(1.0f), 32.0f);
    auto diffuseMaterial = std::make_shared<Material>(glm::vec3(0.5f), glm::vec3(0.7f), glm::vec3(0.0f), 32.0f);
    auto basketballMaterial = std::make_shared<Material>(glm::vec3(0.8f), glm::vec3(0.8f), glm::vec3(0.3f), 32.0f);
    auto nomaiMaterial = std::make_shared<Material>(glm::vec3(0.8f), glm::vec3(0.0f), glm::vec3(0.0f), 32.0f);
    auto matteMaterial = std::make_shared<Material>(glm::vec3(0.8f), glm::vec3(0.0f), glm::vec3(0.0f), 1.0f);
    
    // Models
    auto streetLampModel = std::make_shared<Model>(ModelPaths::streetLight);
    auto basketballModel = std::make_shared<Model>(ModelPaths::basketballB);
    auto benchModel = std::make_shared<Model>(ModelPaths::bench);

    // Nomai Installation
    auto sunNode = std::make_shared<SunNode>(glm::vec3(7.0f, 3.0f, 30.0f), glm::vec3(0.0f), glm::vec3(4.0f),
                                               basketballModel, mainShader, defaultMaterial);
    auto planetNode = std::make_shared<Drone>(glm::vec3(0.3f), basketballModel, mainShader, nomaiMaterial,
                                               glm::vec3(0.0f, 0.0f, 0.0f), 1.2f, 4.5f);
    auto satelliteNode = std::make_shared<Drone>(glm::vec3(0.5f), basketballModel, mainShader, nomaiMaterial,
                                               glm::vec3(0.0f, 0.0f, 0.0f), 0.3f, 2.0f);
    planetNode->AddChild(satelliteNode);
    sunNode->AddChild(planetNode);
    gameObjects.push_back(sunNode);
    gameObjects.push_back(planetNode);
    gameObjects.push_back(satelliteNode);

    // Court
    auto courtModel = std::make_shared<Model>(ModelPaths::courtModel);
    auto court = std::make_shared<ModelObject>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f),
                                               courtModel, mainShader, defaultMaterial);
    gameObjects.push_back(court);

    // Decorations
    gameObjects.push_back(std::make_shared<ModelObject>(glm::vec3(-10.0f, 0.3f, -20.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.03f), benchModel, mainShader, matteMaterial));
    gameObjects.push_back(std::make_shared<ModelObject>(glm::vec3(25.0f, 0.3f, -20.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.03f), benchModel, mainShader, matteMaterial));
    gameObjects.push_back(std::make_shared<ModelObject>(glm::vec3(-10.0f, 0.3f, 20.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.03f), benchModel, mainShader, matteMaterial));
    gameObjects.push_back(std::make_shared<ModelObject>(glm::vec3(25.0f, 0.3f, 20.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.03f), benchModel, mainShader, matteMaterial));
    
    // Animated Objects
    auto logo = std::make_shared<CourtLogo>(glm::vec3(6.75f, 5.8f, -13.4f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(1.0f),
                                           logoMesh, mainShader, defaultMaterial);
    gameObjects.push_back(logo);
    
    gameObjects.push_back(std::make_shared<Counter>(glm::vec3(18.5f, 4.1f, 0.55f), glm::vec3(-90.0f, 0.0f, 90.0f), glm::vec3(0.25f),
                                           counterMesh, animatedShader, defaultMaterial));
    gameObjects.push_back(std::make_shared<Counter>(glm::vec3(-5.45f, 4.1f, 0.55f), glm::vec3(-90.0f, 0.0f, -90.0f), glm::vec3(0.25f),
                                           counterMesh, animatedShader, defaultMaterial));

    // Basketball
    auto basketballCollider = std::make_shared<BasketballObject>(glm::vec3(0.0f, 0.19f, -2.0f), glm::vec3(0.0f), glm::vec3(0.5f));
    gameObjects.push_back(basketballCollider);
    interactableObjects.push_back(basketballCollider);
    
    auto basketball = std::make_shared<ModelObject>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(3.5f),
                                                    basketballModel, mainShader, diffuseMaterial);
    gameObjects.push_back(basketball);
    basketballCollider->AddChild(basketball);
    
    
    // Cubes
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(2.0f, 0.5f, -35.8f), glm::vec3(0.0f), glm::vec3(1.0f),
                                                       greenCubeMesh, mainShader, shinyMaterial));
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(2.0f, 0.8f, -34.0f), glm::vec3(0.0f), glm::vec3(1.5f),
                                                       redCubeMesh, mainShader, defaultMaterial));
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(2.1f, 0.6f, -32.2f), glm::vec3(0.0f), glm::vec3(1.2f),
                                                       blueCubeMesh, mainShader, diffuseMaterial));

    // Switch
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(13.60f, 1.6f, -28.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f),
                                                       grayCubeMesh, mainShader, matteMaterial));
    gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(13.09f, 1.6f, -28.0f), glm::vec3(0.0f, 0.0f, 90.0f), glm::vec3(0.5f),
                                                       buttonBGMesh, mainShader, matteMaterial));
    auto environmentSwitch = std::make_shared<EnvironmentSwitch>(glm::vec3(13.15f, 1.6f, -28.0f), glm::vec3(0.0f), glm::vec3(0.25f),
                                          redCubeMesh, mainShader, matteMaterial);
    gameObjects.push_back(environmentSwitch);
    interactableObjects.push_back(environmentSwitch);

    // Lights
    auto pointLightTextureIds = std::make_shared<std::vector<GLuint>>(
    std::initializer_list<GLuint>{whiteTexture->getTextureID(), redTexture->getTextureID(),greenTexture->getTextureID(),blueTexture->getTextureID()});
    auto pointLight = std::make_shared<PointLight>(glm::vec3(3.5f, 0.5f, -34.2f), glm::vec3(0.0f), glm::vec3(0.2f),
                                                   lightCubeMesh, colorShader, shinyMaterial, pointLightTextureIds);
    interactableObjects.push_back(pointLight);
    gameObjects.push_back(pointLight);

    auto streetLamp = std::make_shared<ModelObject>(glm::vec3(12.0f, 0.0f, -38.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f),
                                                    streetLampModel, mainShader, defaultMaterial);
    gameObjects.push_back(streetLamp);

    auto skyboxFolders = std::make_shared<std::vector<std::string>>(std::initializer_list<std::string>{TexturePaths::blueSkybox}); 
    skybox = std::make_shared<Skybox>(skyboxShader);
    
    GameUtils::GenerateGrid(DebugGrid::size, DebugGrid::step);
    
    SetLightParameters(pointLight, streetLamp);

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
    instance->animatedShader = std::make_shared<ShaderProgram>(ShaderPaths::animatedVertexShader,
                                       ShaderPaths::animatedFragmentShader);
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
