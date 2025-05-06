#include "Game/GameManager.h"


int main(const int argc, char** argv)
{
    GameManager::InitializeGlut(argc, argv);
    GameManager::InitializeFramework();
    auto gameUtils = std::make_unique<GameManager>();
    GameManager::instance->StartGame();
    return 0;
}
