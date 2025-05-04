#include "Game/GameEvents.h"
#include "Game/GameUtils.h"


void GameEvents::DrawWindowContents()
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
    auto direction = glm::vec3(cos(glm::radians(GameUtils::instance->gameInfo.cameraAzimuthAngle)),
                               sin(glm::radians(GameUtils::instance->gameInfo.cameraAzimuthAngle)), 0.0f);

    auto cameraView = direction;
    
    auto rotationAxis = glm::cross(cameraView, cameraUpVector);
    auto rotationMatrix = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(GameUtils::instance->gameInfo.cameraElevationAngle),
                                                rotationAxis));

    auto rotatedView = rotationMatrix * cameraView;
    auto rotatedUp = rotationMatrix * cameraUpVector;

    auto cameraCenter = cameraPosition + rotatedView;
    cameraUpVector = rotatedUp;

    viewMatrix = lookAt(
        cameraPosition,
        cameraCenter,
        cameraUpVector
    );

    projectionMatrix = glm::perspective(glm::radians(60.0f), GameUtils::instance->gameInfo.windowWidth / (float)
                                        GameUtils::instance->gameInfo.windowHeight,
                                        0.1f, 10.0f);

    for (auto gameObject : GameUtils::instance->gameObjects)
    {
        if (auto renderableObject = dynamic_cast<RenderableObject*>(gameObject))
        {
            renderableObject->Render(viewMatrix, projectionMatrix);
        }
    }
}

void GameEvents::OnRenderDisplay()
{
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

    glClear(mask);

    DrawWindowContents();

    glutSwapBuffers();

}

void GameEvents::OnReshapeWindow(int newWidth, int newHeight)
{
    GameUtils::instance->gameInfo.windowWidth = newWidth;
    GameUtils::instance->gameInfo.windowHeight = newHeight;

    glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);
}

void GameEvents::OnTimer(int)
{
    GameUtils::instance->gameInfo.elapsedTime = 0.001f * static_cast<float>(glutGet(GLUT_ELAPSED_TIME)); // milliseconds => seconds

    if (GameUtils::instance->gameInfo.gameOver == true)
    {
        GameUtils::instance->gameInfo.keyMap[KEY_SPACE] = false;
    }

    for (auto gameObject : GameUtils::instance->gameObjects)
    {
        gameObject->Update(GameUtils::instance->gameInfo.elapsedTime);
    }

    glutTimerFunc(33, OnTimer, 0);
    glutPostRedisplay();
}

void GameEvents::OnPassiveMouseMotion(int mouseX, int mouseY)
{
    if (mouseY == GameUtils::instance->gameInfo.windowHeight / 2 && mouseX == GameUtils::instance->gameInfo.windowWidth / 2) return;

    const float cameraElevationAngleDelta = 0.5f * (mouseY - GameUtils::instance->gameInfo.windowHeight / 2);
    const float cameraAzimuthAngleDelta = 0.5f * (mouseX - GameUtils::instance->gameInfo.windowWidth / 2);

    if (fabs(GameUtils::instance->gameInfo.cameraElevationAngle + cameraElevationAngleDelta) < CAMERA_ELEVATION_MAX)
        GameUtils::instance->gameInfo.cameraElevationAngle += cameraElevationAngleDelta;

    GameUtils::instance->gameInfo.cameraAzimuthAngle = fmod(GameUtils::instance->gameInfo.cameraAzimuthAngle + cameraAzimuthAngleDelta, 360.0f);

    glutWarpPointer(GameUtils::instance->gameInfo.windowWidth / 2, GameUtils::instance->gameInfo.windowHeight / 2);

    glutPostRedisplay();
}

void GameEvents::OnKeyPress(unsigned char keyPressed, int mouseX, int mouseY)
{
    switch (keyPressed)
    {
    case 27: // escape
        exit(0);
    default:
        ; // printf("Unrecognized key pressed\n");
    }
}