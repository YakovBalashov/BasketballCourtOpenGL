#include "Game/GameUtils.h"


int main(const int argc, char** argv)
{
    GameUtils::InitializeGlut(argc, argv);
    GameUtils::InitializeFramework();
    auto gameUtils = std::make_unique<GameUtils>();
    GameUtils::instance->StartGame();
    return 0;
}
