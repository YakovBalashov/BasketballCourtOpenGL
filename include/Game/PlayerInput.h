#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

class PlayerInput
{
public:
    static std::unordered_map<unsigned char, glm::vec2> keyToDirection;
    static std::unordered_map<unsigned char, void (*)(unsigned char)> keyPressToMethod;
    static std::unordered_map<unsigned char, void (*)(unsigned char)> keyReleaseToMethod;
    static std::unordered_map<unsigned char, void (*)(unsigned char)> specialKeyPressToMethod;
    static std::unordered_map<unsigned char, void(*)(unsigned char)> specialKeyReleaseToMethod;
    static bool isFullscreen;
    static bool isFlashLightOn;

    static void OnKeyPress(unsigned char keyPressed, int mousePositionX, int mousePositionY);

    static void OnKeRelease(unsigned char keyReleased, int mousePositionX, int mousePositionY);

    static void OnSpecialKeyPress(int keyPressed, int mousePositionX, int mousePositionY);

    static void OnSpecialKeyRelease(int keyReleased, int mousePositionX, int mousePositionY);
    
    static void SetPlayerDirection(unsigned char input);

    static void ResetPlayerDirection(unsigned char input);

    static void ActivatePlayerSprint(unsigned char input);

    static void FinishGame(unsigned char input);

    static void ToggleFullscreen(unsigned char input);

    static void DeactivatePlayerSprint(unsigned char input);
    
    static void CycleCamera(unsigned char input);

    static void ToggleFlashLight(unsigned char input);
    
    static void NextCamera(unsigned char input);
    
    static void PreviousCamera(unsigned char input);
    
    static void TogglePickingMode(unsigned char input);
};
