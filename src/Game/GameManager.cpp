#include "Game/GameManager.h"

#include "Game/meshes.h"
#include "Game/PlayerInput.h"
#include "GameObjects/Drone.h"
#include "GameObjects/Camera.h"
#include "GameObjects/ModelObject.h"
#include "GameObjects/Skybox.h"
#include "GameObjects/TestObject.h"
#include "Rendering/Texture.h"
#include "Rendering/Material.h"


std::unique_ptr<GameManager> GameManager::instance = nullptr;

GLfloat testVertices[] = {
    -0.5f, 0.0f, 0.5f,
    -0.5f, 0.0f, -0.5f,
    0.5f, 0.0f, -0.5f,
    0.5f, 0.0f, 0.5f,
    0.0f, 0.8f, 0.0f,
};

GLuint testIndices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

std::vector<Vertex> groundVertices = {
    {{-Ground::size, 0.0f, -Ground::size}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},  // Bottom-left
    {{ Ground::size, 0.0f, -Ground::size}, {0.0f, 1.0f, 0.0f}, {Ground::size, 0.0f}}, // Bottom-right
    {{ Ground::size, 0.0f,  Ground::size}, {0.0f, 1.0f, 0.0f}, {Ground::size, Ground::size}}, // Top-right
    {{-Ground::size, 0.0f,  Ground::size}, {0.0f, 1.0f, 0.0f}, {0.0f, Ground::size}}, // Top-left
};

std::vector<GLuint> groundIndices = {
    0, 1, 2,
    0, 2, 3
};

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
    glutSetCursor(GLUT_CURSOR_NONE);

    glutTimerFunc(33, GameEvents::OnTimer, 0);
    glutWMCloseFunc(FinalizeGame);
}

void GameManager::SetupCameras()
{
    playerCamera = std::make_shared<PlayerCamera>(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    cameras.push_back(playerCamera);
    gameObjects.push_back(playerCamera);

    auto staticCameraA = std::make_shared<Camera>(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f), glm::vec3(1.0f));
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
    srand((unsigned int)time(NULL));

    // initialize OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    InitializeShaders();
    InitializeModels();

    // GenerateDebugGrid();

    SetupCameras();

    auto concreteTexture = std::make_shared<Texture>("assets/textures/concrete_a.jpg");
    auto redTexture = std::make_shared<Texture>(TexturePaths::red);
    auto concreteMesh = std::make_shared<Mesh>(groundVertices, groundIndices, concreteTexture->getTextureID());
    auto testMesh = std::make_shared<Mesh>(static_cast<const GLfloat*>(testVertices),static_cast<const GLuint*>(testIndices),5, 6);

    auto defaultMaterial = std::make_shared<Material>();
    auto shinyMaterial = std::make_shared<Material>(glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f), 32.0f);
    
    auto courtModel = std::make_shared<Model>(ModelPaths::courtModel);
    auto court = std::make_shared<ModelObject>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), courtModel, mainShader, defaultMaterial);
    gameObjects.push_back(court);
    
    auto basketballModel = std::make_shared<Model>(ModelPaths::basketballModel);
    auto basketball = std::make_shared<ModelObject>(glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), basketballModel, mainShader, defaultMaterial);

    auto portalCubeModel = std::make_shared<Model>(ModelPaths::portalCube);
    auto portalCube = std::make_shared<ModelObject>(glm::vec3(2.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f),
                                                    portalCubeModel, mainShader, defaultMaterial);
    gameObjects.push_back(portalCube);
    
    auto cubeMesh = std::make_shared<Mesh>(MeshVertices::cubeVertices, MeshVertices::cubeIndices, redTexture->getTextureID());
    auto cube = std::make_shared<MeshObject>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), cubeMesh, mainShader, shinyMaterial);
    gameObjects.push_back(cube);
    
    skybox = std::make_shared<Skybox>(skyboxShader);

    // gameObjects.push_back(currentCamera);
    // gameObjects.push_back(basketball);
    // gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), concreteMesh, mainShader));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(1.0f), testMesh, mainShader, defaultMaterial));

    mainShader->UseProgram();
    mainShader->SetAmbientLight(LightsConfig::ambientColor, LightsConfig::ambientIntensity);
    mainShader->SetDirectionalLightColor(glm::vec3(0.3f));
    
    
    gameInfo.cameraAzimuthAngle = 0.0f;
    gameInfo.cameraElevationAngle = 0.0f;
    glutMainLoop();
}

void GameManager::CycleCamera()
{
    currentCameraIndex = (currentCameraIndex + 1) % static_cast<int>(cameras.size());
    currentCamera = cameras[currentCameraIndex];
}

void GameManager::InitializeShaders()
{
    instance->mainShader = std::make_shared<ShaderProgram>(ShaderPaths::simpleVertexShader, ShaderPaths::simpleFragmentShader);
    instance->skyboxShader = std::make_shared<ShaderProgram>(ShaderPaths::skyboxVertexShader, ShaderPaths::skyboxFragmentShader);
    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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


