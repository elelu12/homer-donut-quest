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
    int totalCount() const { return static_cast<int>(m_donuts.size()); }


private:
    Player m_player;
    std::vector<DonutInstance> m_donuts;
};
