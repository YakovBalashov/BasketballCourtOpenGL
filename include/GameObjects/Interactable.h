/**
* \file Interactable.h
 * \author Yakov Balashov
 * \date Summer Semester 2025
 * \brief Interface for interactable objects in the game.
 */

#pragma once

class Interactable 
{
public:
    /**
     * Called when player uses mouse to interact with the object.
     */
    virtual void Interact() = 0;
};
