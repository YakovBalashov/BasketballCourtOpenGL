#include <Game/GameUtils.h>

float GameUtils::Repeat(float value, float max)
{
    return fmod(fmod(value, max) + max, max);
}
