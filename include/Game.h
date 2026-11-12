#pragma once
#include "Player.h"
#include <glm/glm.hpp>

// Stato della prima prova di raccolta, separato dalla geometria.
class Game
{
public:
    void update(glm::vec2 direction, float deltaTime);
    void reset() { *this = Game{}; }
    const Player& player() const { return m_player; }
    bool donutVisible() const { return !m_collected; }
    int collectedCount() const { return m_collected ? 1 : 0; }
    glm::vec2 donutPosition() const { return {0.65f, 0.35f}; }
    float donutRadius() const { return 0.22f; }
private:
    Player m_player;
    bool m_collected = false;
};
