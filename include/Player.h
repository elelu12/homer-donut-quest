#pragma once
#include <glm/glm.hpp>

// Stato del personaggio separato dalla geometria di Homer.
class Player
{
public:
    void update(glm::vec2 direction, float deltaTime);
    glm::mat4 modelMatrix() const;
    glm::vec2 position() const { return m_position; }
    glm::vec2 halfSize() const { return glm::vec2(0.40f, 0.73f) * m_scale; }
private:
    glm::vec2 m_position{0.60f, -0.55f};
    float m_scale = 0.30f;
    float m_speed = 0.75f; // Unità di scena al secondo.
};
