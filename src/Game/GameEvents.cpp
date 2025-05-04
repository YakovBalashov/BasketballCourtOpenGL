#include "Game/GameEvents.h"
#include "Game/GameUtils.h"

void GameEvents::OnRenderDisplay()
{
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(mask);

    auto viewMatrix = GameUtils::instance->playerCamera->GetViewMatrix();

    auto projectionMatrix = glm::perspective(glm::radians(60.0f), GameUtils::instance->gameInfo.windowWidth / (float)
                                             GameUtils::instance->gameInfo.windowHeight,
                                             0.1f, 10.0f);

    for (auto gameObject : GameUtils::instance->gameObjects)
    {
        if (auto renderableObject = dynamic_cast<RenderableObject*>(gameObject.get()))
        {
            renderableObject->Render(viewMatrix, projectionMatrix);
        }
    }

    glutSwapBuffers();
}

void GameEvents::OnReshapeWindow(int newWidth, int newHeight)
{
    GameUtils::instance->gameInfo.windowWidth = newWidth;
    GameUtils::instance->gameInfo.windowHeight = newHeight;

    glViewport(0, 0, newWidth, newHeight);
}

void GameEvents::OnTimer(int)
{
    GameUtils::instance->gameInfo.elapsedTime = 0.001f * static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
    // milliseconds => seconds

    for (auto gameObject : GameUtils::instance->gameObjects)
    {
        gameObject->Update(GameUtils::instance->gameInfo.elapsedTime);
    }

    glutTimerFunc(33, OnTimer, 0);
    glutPostRedisplay();
}

void GameEvents::OnPassiveMouseMotion(int mousePositionX, int mousePositionY)
{
    if (mousePositionY == GameUtils::instance->gameInfo.windowHeight / 2 && mousePositionX == GameUtils::instance->
        gameInfo.windowWidth / 2) return;

    GameUtils::instance->playerCamera->UpdateOrientation(mousePositionX, mousePositionY);

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
