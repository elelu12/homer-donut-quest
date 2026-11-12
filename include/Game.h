#pragma once
#include "Player.h"
#include <glm/glm.hpp>
#include <vector>

// Stato di una singola istanza: la geometria Donut rimane condivisa.
struct DonutInstance
{
    glm::vec2 position;
    float radius;
    float angle;
    bool collected = false;
};

// Stato della raccolta, separato dalla geometria.
// separiamo logica da gioco dal rendering
class Game
{
public:
    void update(glm::vec2 direction, float deltaTime);
    Game();
    void reset();
    const Player& player() const { return m_player; }
    const std::vector<DonutInstance>& donuts() const { return m_donuts; }
    int collectedCount() const;
    glm::vec2 broccoliPosition() const;
    float broccoliScale() const { return 0.14f; }
    glm::vec2 broccoliHalfSize() const { return glm::vec2(0.84f,0.90f)*broccoliScale(); }
    glm::vec2 beerPosition() const { return {8.5f,-0.60f}; }
    glm::vec2 beerScale() const { return {0.20f,0.183f}; }
    bool beerCollected() const { return m_beerCollected; }
    int score() const { return collectedCount() + (m_beerCollected ? 2 : 0); }
    bool hitFeedback() const { return m_hitTimer > 0; }
    int totalCount() const { return static_cast<int>(m_donuts.size()); }


private:
    bool m_beerCollected = false;
    float m_time = 0;
    float m_hitTimer = 0;
    Player m_player;
    std::vector<DonutInstance> m_donuts;
};
