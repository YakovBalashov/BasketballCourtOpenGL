#include "Game/GameManager.h"

#include "Game/PlayerInput.h"
#include "GameObjects/ModelObject.h"
#include "GameObjects/Skybox.h"
#include "GameObjects/TestObject.h"
#include "Rendering/Texture.h"


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

    GenerateDebugGreed();

    auto concreteTexture = std::make_shared<Texture>("assets/textures/concrete_a.jpg");
    auto concreteMesh = std::make_shared<Mesh>(groundVertices, groundIndices, concreteTexture->getTextureID());
    auto testMesh = std::make_shared<Mesh>(static_cast<const GLfloat*>(testVertices),static_cast<const GLuint*>(testIndices),5, 6);

    auto courtModel = std::make_shared<Model>(ModelPaths::courtModel);
    auto court = std::make_shared<ModelObject>(glm::vec3(0.0f, -1.5f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), courtModel, mainShader);

    auto basketballModel = std::make_shared<Model>(ModelPaths::basketballModel);
    auto basketball = std::make_shared<ModelObject>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.02f), basketballModel, mainShader);
    
    skybox = std::make_shared<Skybox>(skyboxShader);
    currentCamera = std::make_shared<PlayerCamera>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    gameObjects.push_back(currentCamera);
    gameObjects.push_back(basketball);
    gameObjects.push_back(court);
    // gameObjects.push_back(std::make_shared<MeshObject>(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f), concreteMesh, mainShader));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(1.0f), testMesh, mainShader));


    gameInfo.cameraAzimuthAngle = 0.0f;
    gameInfo.cameraElevationAngle = 0.0f;
    glutMainLoop();
}

void GameManager::InitializeShaders()
{
    instance->mainShader = std::make_shared<ShaderProgram>(ShaderPaths::simpleVertexShader, ShaderPaths::simpleFragmentShader);
    instance->skyboxShader = std::make_shared<ShaderProgram>(ShaderPaths::skyboxVertexShader, ShaderPaths::skyboxFragmentShader);
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

void GameManager::GenerateDebugGreed()
{
    // auto debugTexture = std::make_shared<Texture>("assets/textures/debug.jpg");
    // auto concreteMesh = std::make_shared<Mesh>(groundVertices, groundIndices, concreteTexture->getTextureID());

}
