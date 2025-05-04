#include "Game/GameUtils.h"


int main(const int argc, char** argv)
{
    GameUtils::SetupApp(argc, argv);
    GameUtils::InitializeFramework();
    auto gameUtils = std::make_unique<GameUtils>();
    GameUtils::instance->StartApp();
    return 0;
}
