#include "Game/GameUtils.h"
#include "GameObjects/TestObject.h"


std::unique_ptr<GameUtils> GameUtils::instance = nullptr;

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

GameUtils::GameUtils()
{
    if (instance) return;
    instance = std::unique_ptr<GameUtils>(this);
}

void GameUtils::InitializeGlut(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

    glutInitWindowSize(Window::width, Window::height);
    glutCreateWindow(Window::title);

    glutDisplayFunc(GameEvents::OnRenderDisplay);
    glutReshapeFunc(GameEvents::OnReshapeWindow);
    glutKeyboardFunc(GameEvents::OnKeyPress);
    glutPassiveMotionFunc(GameEvents::OnPassiveMouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);

    glutTimerFunc(33, GameEvents::OnTimer, 0);
    glutWMCloseFunc(FinalizeGame);
}

void GameUtils::InitializeFramework()
{
    if (pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) return;
    pgr::dieWithError("PGR Framework Initialization Failed");
}

void GameUtils::StartGame()
{
    // initialize random seed
    srand((unsigned int)time(NULL));

    // initialize OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    InitializeShaders();
    InitializeModels();

    playerCamera = std::make_shared<CameraObject>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

    gameObjects.push_back(playerCamera);
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(5.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(5.0f, 0.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(5.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(5.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(std::make_shared<TestObject>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(1.0f)));


    gameInfo.cameraAzimuthAngle = 0.0f;
    gameInfo.cameraElevationAngle = 0.0f;
    glutMainLoop();
}

void GameUtils::InitializeShaders()
{
    instance->mainShader = std::make_unique<ShaderProgram>("Shaders/simple.vert", "Shaders/simple.frag");
}

void GameUtils::InitializeModels()
{
    TestObject::CreateMesh(testVertices, testIndices, sizeof(testVertices), sizeof(testIndices));
}

void GameUtils::FinalizeGame()
{
    
}

void GameUtils::PrintGPUInfo()
{
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);

    std::cout << "GPU Vendor:   " << vendor << '\n';
    std::cout << "GPU Renderer: " << renderer << '\n';
    std::cout << "OpenGL Version: " << version << '\n';
}
