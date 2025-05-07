#include "Game/GameEvents.h"
#include "Game/GameManager.h"

void GameEvents::OnRenderDisplay()
{
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(mask);

    auto viewMatrix = GameManager::instance->playerCamera->GetViewMatrix();

    auto projectionMatrix = glm::perspective(glm::radians(Camera::fovy), static_cast<float>(GameManager::instance->gameInfo.windowWidth) / GameManager::instance->gameInfo.windowHeight,
                                             Camera::nearPlane, Camera::farPlane);
    
    GameManager::instance->skybox->Render(viewMatrix, projectionMatrix);
    for (const auto& gameObject : GameManager::instance->gameObjects)
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
    GameManager::instance->gameInfo.windowWidth = newWidth;
    GameManager::instance->gameInfo.windowHeight = newHeight;

    glViewport(0, 0, newWidth, newHeight);
}

void GameEvents::OnTimer(int)
{
    auto currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME)) * millisecondsToSeconds;
    GameManager::instance->gameInfo.deltaTime = currentTime - GameManager::instance->gameInfo.currentTime;
    GameManager::instance->gameInfo.currentTime = currentTime;

    for (const auto& gameObject : GameManager::instance->gameObjects)
    {
        gameObject->Update();
    }

    glutTimerFunc(33, OnTimer, 0);
    glutPostRedisplay();
}

void GameEvents::OnPassiveMouseMotion(int mousePositionX, int mousePositionY)
{
    if (mousePositionY == GameManager::instance->gameInfo.windowHeight / 2 && mousePositionX == GameManager::instance->
        gameInfo.windowWidth / 2) return;

    GameManager::instance->playerCamera->UpdateOrientation(mousePositionX, mousePositionY);

    glutWarpPointer(GameManager::instance->gameInfo.windowWidth / 2, GameManager::instance->gameInfo.windowHeight / 2);

    glutPostRedisplay();
}

// void GameEvents::OnKeyPress(unsigned char keyPressed, int mouseX, int mouseY)
// {
//     switch (keyPressed)
//     {
//     case 27: // escape
//         exit(0);
//     default:
//         ; // printf("Unrecognized key pressed\n");
//     }
// }
