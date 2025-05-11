#include "Game/GameEvents.h"
#include "Game/GameManager.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Interactable.h"

void GameEvents::OnRenderDisplay()
{
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(mask);

    auto viewMatrix = GameManager::instance->currentCamera->GetViewMatrix();

    GameManager::instance->mainShader->UseProgram();
    GameManager::instance->mainShader->SetCameraPosition(GameManager::instance->currentCamera->GetPosition());
    GameManager::instance->mainShader->SetTime(GameManager::instance->gameInfo.currentTime);

    auto projectionMatrix = glm::perspective(glm::radians(CameraConfig::fovy),
                                             static_cast<float>(GameManager::instance->gameInfo.windowWidth) /
                                             static_cast<float>(GameManager::instance->gameInfo.windowHeight),
                                             CameraConfig::nearPlane, CameraConfig::farPlane);

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

    glutPostRedisplay();
    glutTimerFunc(33, OnTimer, 0);
}

void GameEvents::OnPassiveMouseMotion(int mousePositionX, int mousePositionY)
{
    if (GameManager::instance->gameInfo.isPickingMode) return;
    if (mousePositionY == GameManager::instance->gameInfo.windowHeight / 2 && mousePositionX == GameManager::instance->
        gameInfo.windowWidth / 2)
        return;

    GameManager::instance->playerCamera->UpdateOrientation(mousePositionX, mousePositionY);

    glutWarpPointer(GameManager::instance->gameInfo.windowWidth / 2, GameManager::instance->gameInfo.windowHeight / 2);

    glutPostRedisplay();
}

glm::vec3 GameEvents::GetMouseRayDirection(int positionX, int positionY)
{
    auto screenWidth = GameManager::instance->gameInfo.windowWidth;
    auto screenHeight = GameManager::instance->gameInfo.windowHeight;

    float x = (2.0f * static_cast<float>(positionX)) / static_cast<float>(screenWidth) - 1.0f;
    float y = 1.0f - (2.0f * static_cast<float>(positionY)) / static_cast<float>(screenHeight);
    glm::vec4 rayNDC(x, y, -1.0f, 1.0f);

    auto projectionMatrix = glm::perspective(glm::radians(CameraConfig::fovy),
                                             static_cast<float>(GameManager::instance->gameInfo.windowWidth) /
                                             static_cast<float>(GameManager::instance->gameInfo.windowHeight),
                                             CameraConfig::nearPlane, CameraConfig::farPlane);
    glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayNDC;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

    glm::mat4 viewMatrix = GameManager::instance->currentCamera->GetViewMatrix();
    glm::vec3 rayWorld = glm::normalize(glm::vec3(glm::inverse(viewMatrix) * rayEye));
    return rayWorld;
}

bool GameEvents::IsPassingTrough(glm::vec3 mouseRayDirection, glm::vec3 cameraPosition, const std::vector<std::shared_ptr<GameObject>>::value_type& gameObject)
{
    glm::vec3 oc = cameraPosition - gameObject->GetPosition();
    float b = glm::dot(oc, mouseRayDirection);
    float radius = gameObject->GetScale().x / 2.0f;
    float c = glm::dot(oc, oc) - radius * radius;
    float discriminant = b * b - c;
    return discriminant >= 0.0f;
}

void GameEvents::OnMouseAction(int button, int state, int positionX, int positionY)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_UP) return;

    auto mouseRayDirection = GetMouseRayDirection(positionX, positionY);
    auto cameraPosition = GameManager::instance->currentCamera->GetPosition();

    for (const auto& gameObject : GameManager::instance->interactableObjects)
    {
        if (auto interactableObject = dynamic_cast<Interactable*>(gameObject.get()))
        {
            if (!IsPassingTrough(mouseRayDirection, cameraPosition, gameObject)) continue;
            interactableObject->Interact();
        }
    }
}
