#pragma once

class Interactable 
{
public:
    /**
     * Called when player uses mouse to interact with the object.
     */
    virtual void Interact() = 0;
};
