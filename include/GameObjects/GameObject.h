#pragma once
#include "pgr.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject() = default;

    GameObject(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    virtual ~GameObject() = default;

    /**
     * Called once per frame to update the game object.
     */
    virtual void Update()
    {
    }

    /**
     * 
     * @return World position.
     */
    glm::vec3 GetPosition() const;
    
    /**
     * 
     * @return World rotation.
     */
    glm::vec3 GetRotation() const;

    /**
     * 
     * @return World scale.
     */
    glm::vec3 GetScale() const;

    /**
     * 
     * @return Position relative to the parent.
     */
    glm::vec3 GetRelativePosition() const { return position; }

    /**
     * 
     * @return Rotation relative to the parent.
     */
    glm::vec3 GetRelativeRotation() const { return rotation; }

    /**
     * 
     * @return Scale relative to the parent.
     */
    glm::vec3 GetRelativeScale() const { return scale; }

    /**
     * Add a transform child object to the current game object.
     * @param child Transform child object.
     */
    void AddChild(const std::shared_ptr<GameObject>& child);

    /**
     * Set the transform position.
     * @param newParent Transform parent object.
     */
    void SetParent(const std::shared_ptr<GameObject>& newParent);
    

protected:
    void SetPosition(const glm::vec3& newPosition);

    void SetRotation(const glm::vec3& newRotation);

    void SetScale(const glm::vec3& newScale);

private:
    std::vector<std::shared_ptr<GameObject>> children;

    std::shared_ptr<GameObject> parent;
    
    glm::vec3 position = glm::vec3(0.0f);

    glm::vec3 rotation = glm::vec3(0.0f);

    glm::vec3 scale = glm::vec3(1.0f);
};
