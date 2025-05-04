#include "Game/GameUtils.h"
#include "GameObjects/TestObject.h"


std::unique_ptr<GameUtils> GameUtils::instance = nullptr;

GameUtils::GameUtils()
{
    if (instance) return;
    instance = std::unique_ptr<GameUtils>(this);
}

void GameUtils::SetupApp(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

    // initial window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);

    glutDisplayFunc(GameEvents::OnRenderDisplay);
    // register callback for change of window size
    glutReshapeFunc(GameEvents::OnReshapeWindow);
    // register callbacks for keyboard
    glutKeyboardFunc(GameEvents::OnKeyPress);
    glutPassiveMotionFunc(GameEvents::OnPassiveMouseMotion);
    glutSetCursor(GLUT_CURSOR_NONE);

    glutTimerFunc(33, GameEvents::OnTimer, 0);
    glutWMCloseFunc(FinalizeApplication);
}

void GameUtils::InitializeFramework()
{
    if (pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) return;
    pgr::dieWithError("PGR Framework Initialization Failed");
}

void GameUtils::StartApp()
{
    // initialize random seed
    srand((unsigned int)time(NULL));

    // initialize OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    InitializeShaders();
    InitializeModels();

    gameObjects.push_back(new TestObject(glm::vec3(5.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 0.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));


    gameInfo.cameraAzimuthAngle = 0.0f;
    gameInfo.cameraElevationAngle = 0.0f;
    glutMainLoop();
}

void GameUtils::FinalizeApplication()
{
    
}

void GameUtils::InitializeShaders()
{
    instance->mainShader = std::make_unique<ShaderProgram>("Shaders/simple.vert", "Shaders/simple.frag");
}

void GameUtils::InitializeModels()
{
    TestObject::CreateMesh(testVertices, testIndices, sizeof(testVertices), sizeof(testIndices));
}

void GameUtils::PrintGPUInfo()
{
    const GLubyte* renderer = glGetString(GL_RENDERER); // GPU renderer string
    const GLubyte* vendor = glGetString(GL_VENDOR); // GPU vendor string
    const GLubyte* version = glGetString(GL_VERSION); // OpenGL version string

    std::cout << "GPU Vendor:   " << vendor << '\n';
    std::cout << "GPU Renderer: " << renderer << '\n';
    std::cout << "OpenGL Version: " << version << '\n';
}
