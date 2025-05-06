#include <Game/PlayerInput.h>
#include <Game/GameManager.h>

using KeyMethod = void (*)(unsigned char);

std::unordered_map<unsigned char, void (*)(unsigned char)> PlayerInput::keyPressToMethod = {
    std::pair<const unsigned char, KeyMethod>{Input::moveForward, &PlayerInput::SetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::moveBackward, &PlayerInput::SetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::moveLeft, &PlayerInput::SetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::moveRight, &PlayerInput::SetPlayerDirection},
};

std::unordered_map<unsigned char, void (*)(unsigned char)> PlayerInput::keyReleaseToMethod{
    std::pair<const unsigned char, KeyMethod>{Input::moveForward, &PlayerInput::ResetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::moveBackward, &PlayerInput::ResetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::moveLeft, &PlayerInput::ResetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::moveRight, &PlayerInput::ResetPlayerDirection},
    std::pair<const unsigned char, KeyMethod>{Input::exitGame, &PlayerInput::FinishGame},
    std::pair<const unsigned char, KeyMethod>{Input::toggleFullscreen, &PlayerInput::ToggleFullscreen},
};

std::unordered_map<unsigned char, void (*)(unsigned char)> PlayerInput::specialKeyPressToMethod{
    std::pair<const unsigned char, KeyMethod>{Input::sprint, &PlayerInput::ActivatePlayerSprint},
};

std::unordered_map<unsigned char, void (*)(unsigned char)> PlayerInput::specialKeyReleaseToMethod{
    std::pair<const unsigned char, KeyMethod>{Input::sprint, &PlayerInput::DeactivatePlayerSprint},
};

bool PlayerInput::IsFullscreen = true;


std::unordered_map<unsigned char, glm::vec2> PlayerInput::keyToDirection = {
    {'w', {1.0f, 0.0f}},
    {'s', {-1.0f, 0.0f}},
    {'a', {0.0f, -1.0f}},
    {'d', {0.0f, 1.0f}}
};



void PlayerInput::OnKeyPress(unsigned char keyPressed, int mousePositionX, int mousePositionY)
{
    keyPressed = static_cast<unsigned char>(std::tolower(keyPressed));
    const auto it = keyPressToMethod.find(keyPressed);
    if (it == keyPressToMethod.end()) return;
    it->second(keyPressed);
}


void PlayerInput::OnKeRelease(unsigned char keyReleased, int mousePositionX, int mousePositionY)
{
    keyReleased = static_cast<unsigned char>(std::tolower(keyReleased));
    const auto it = keyReleaseToMethod.find(keyReleased);
    if (it == keyReleaseToMethod.end()) return;
    it->second(keyReleased);
}

void PlayerInput::OnSpecialKeyPress(int keyPressed, int mousePositionX, int mousePositionY)
{
    const auto it = specialKeyPressToMethod.find(keyPressed);
    if (it == specialKeyPressToMethod.end()) return;
    it->second(keyPressed);
}

void PlayerInput::OnSpecialKeyRelease(int keyReleased, int mousePositionX, int mousePositionY)
{
    const auto it = specialKeyReleaseToMethod.find(keyReleased);
    if (it == specialKeyReleaseToMethod.end()) return;
    it->second(keyReleased);
}

void PlayerInput::SetPlayerDirection(unsigned char input)
{
    GameManager::instance->playerCamera->SetMovementDirection(keyToDirection[input]);
}

void PlayerInput::ResetPlayerDirection(unsigned char input)
{
    GameManager::instance->playerCamera->StopMovementInDirection(keyToDirection[input]);
}

void PlayerInput::ActivatePlayerSprint(unsigned char input)
{
    GameManager::instance->playerCamera->isSprinting = true;
}

void PlayerInput::FinishGame(unsigned char input)
{
    GameManager::FinalizeGame();
}

void PlayerInput::DeactivatePlayerSprint(unsigned char input)
{
    GameManager::instance->playerCamera->isSprinting = false;
}

void PlayerInput::ToggleFullscreen(unsigned char input)
{
    if (IsFullscreen)
    {
        glutLeaveFullScreen();
        IsFullscreen = false;
        return;
    }
    glutFullScreen();
    IsFullscreen = true;
}
