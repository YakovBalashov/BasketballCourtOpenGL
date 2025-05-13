/**
* \file basketball.cpp
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Main entry point for the basketball game.
 */

#include "Game/GameManager.h"


int main(const int argc, char** argv)
{
    GameManager::InitializeGlut(argc, argv);
    GameManager::InitializeFramework();
    auto gameUtils = std::make_unique<GameManager>();
    GameManager::instance->StartGame();
    return 0;
}
