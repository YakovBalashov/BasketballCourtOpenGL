#include <ctime>
#include <algorithm>
#include <iostream>
#include <list>

#include "pgr.h"
#include "rendering.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/TestObject.h"
#include "data.h"

typedef std::list<void*> GameObjectsList;

struct GameInformation
{
    int windowWidth; // set by reshape callback
    int windowHeight; // set by reshape callback

    float cameraElevationAngle; // in degrees = initially 0.0f
    float cameraAzimuthAngle; // in degrees = initially 0.0f

    bool gameOver; // false;
    bool keyMap[KEYS_COUNT]; // false

    float elapsedTime;
    float missileLaunchTime;
    float ufoMissileLaunchTime;
} gameInfo;

static std::list<GameObject*> gameObjects;

void cleanUpObjects()
{
    /*for (auto gameObject : gameObjects)
    {
        delete gameObject;
    }*/
}

void restartGame()
{
    cleanUpObjects();

    gameInfo.elapsedTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds

    gameInfo.cameraElevationAngle = 0.0f;

    // reset key map
    for (int i = 0; i < KEYS_COUNT; i++)
        gameInfo.keyMap[i] = false;

    gameInfo.gameOver = false;
}

void drawWindowContents()
{
    const glm::mat4 orthoProjectionMatrix = glm::ortho(
        -SCENE_WIDTH, SCENE_WIDTH,
        -SCENE_HEIGHT, SCENE_HEIGHT,
        -10.0f * SCENE_DEPTH, 10.0f * SCENE_DEPTH
    );

    const glm::mat4 orthoViewMatrix = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 viewMatrix = orthoViewMatrix;
    glm::mat4 projectionMatrix = orthoProjectionMatrix;

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUpVector = glm::vec3(0.0f, 0.0f, 1.0f);
    auto direction = glm::vec3(cos(glm::radians(gameInfo.cameraAzimuthAngle)),
                               sin(glm::radians(gameInfo.cameraAzimuthAngle)), 0.0f);
    glm::vec3 cameraCenter = cameraPosition + direction;
    auto cameraView = cameraCenter - cameraPosition;

    auto rotationAxis = glm::cross(cameraView, cameraUpVector);
    auto rotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(gameInfo.cameraElevationAngle),
                                                rotationAxis));

    auto rotatedView = rotationMatrix * cameraView;
    auto rotatedUp = rotationMatrix * cameraUpVector;

    cameraCenter = cameraPosition + rotatedView;
    cameraUpVector = rotatedUp;

    viewMatrix = lookAt(
        cameraPosition,
        cameraCenter,
        cameraUpVector
    );

    projectionMatrix = glm::perspective(glm::radians(60.0f), gameInfo.windowWidth / (float)gameInfo.windowHeight,
                                        0.1f, 10.0f);

    for (auto gameObject : gameObjects)
    {
        if (auto renderableObject = dynamic_cast<RenderableObject*>(gameObject))
        {
            renderableObject->Render(viewMatrix, projectionMatrix);
        }
    }

    // std::cout << gameState.cameraAzimuthAngle << " " << gameState.cameraElevationAngle << std::endl;
}


void displayCallback()
{
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    glClear(mask);

    drawWindowContents();

    glutSwapBuffers();
}

void reshapeCallback(int newWidth, int newHeight)
{
    gameInfo.windowWidth = newWidth;
    gameInfo.windowHeight = newHeight;

    glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
}

// Callback responsible for the scene update
void timerCallback(int)
{
    gameInfo.elapsedTime = 0.001f * static_cast<float>(glutGet(GLUT_ELAPSED_TIME)); // milliseconds => seconds

    if (gameInfo.gameOver == true)
    {
        gameInfo.keyMap[KEY_SPACE] = false;
    }

    for (auto gameObject : gameObjects)
    {
        gameObject->Update(gameInfo.elapsedTime);
    }

    glutTimerFunc(33, timerCallback, 0);
    glutPostRedisplay();
}

// Called when mouse is moving while no mouse buttons are pressed.
void passiveMouseMotionCallback(int mouseX, int mouseY)
{
    if (mouseY == gameInfo.windowHeight / 2 && mouseX == gameInfo.windowWidth / 2) return;

    const float cameraElevationAngleDelta = 0.5f * (mouseY - gameInfo.windowHeight / 2);
    const float cameraAzimuthAngleDelta = 0.5f * (mouseX - gameInfo.windowWidth / 2);

    if (fabs(gameInfo.cameraElevationAngle + cameraElevationAngleDelta) < CAMERA_ELEVATION_MAX)
        gameInfo.cameraElevationAngle += cameraElevationAngleDelta;

    gameInfo.cameraAzimuthAngle = fmod(gameInfo.cameraAzimuthAngle + cameraAzimuthAngleDelta, 360.0f);

    glutWarpPointer(gameInfo.windowWidth / 2, gameInfo.windowHeight / 2);

    glutPostRedisplay();
}

void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY)
{
    switch (keyPressed)
    {
    case 27: // escape
        exit(0);
        break;
    default:
        ; // printf("Unrecognized key pressed\n");
    }
}

void startApp()
{
    // initialize random seed
    srand((unsigned int)time(NULL));

    // initialize OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    initializeShaders();

    initializeModels();

    gameObjects.push_back(new TestObject(glm::vec3(5.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 0.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
    gameObjects.push_back(new TestObject(glm::vec3(5.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));

    restartGame();
}

void finalizeApplication(void)
{
    cleanUpObjects();

    cleanupModels();

    cleanupShaders();
}

void SetupApp(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

    // initial window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);

    glutDisplayFunc(displayCallback);
    // register callback for change of window size
    glutReshapeFunc(reshapeCallback);
    // register callbacks for keyboard
    glutKeyboardFunc(keyboardCallback);
    glutPassiveMotionFunc(passiveMouseMotionCallback);
    glutSetCursor(GLUT_CURSOR_NONE);

    glutTimerFunc(33, timerCallback, 0);
}

void InitializeFramework()
{
    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
}

int main(const int argc, char** argv)
{
    SetupApp(argc, argv);

    InitializeFramework();

    startApp();

    glutWMCloseFunc(finalizeApplication);
    glutMainLoop();

    return 0;
}
