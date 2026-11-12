#include "Game.h"
#include <glm/common.hpp>

Game::Game()
{
    reset();
}

void Game::reset()
{
    m_player = Player{};
    // Cinque stati indipendenti; nessuna copia dei vertici della mesh.
    m_donuts = {
        {{-0.72f, -0.70f}, 0.105f,  0.15f, false},
        {{-0.10f, -0.65f}, 0.115f, -0.35f, false},
        {{ 0.55f, -0.72f}, 0.105f,  0.60f, false},
        {{ 0.60f,  0.45f}, 0.120f, -0.20f, false},
        {{ 0.00f,  0.65f}, 0.110f,  0.40f, false}
    };
}

int Game::collectedCount() const
{
    int count = 0;
    for (const DonutInstance& donut : m_donuts)
        if (donut.collected) ++count;
    return count;
}

void Game::update(glm::vec2 direction, float deltaTime)
{
    m_player.update(direction, deltaTime);
    const glm::vec2 halfSize = m_player.halfSize();
    const glm::vec2 center = m_player.position();
    for (DonutInstance& donut : m_donuts)
    {
        if (donut.collected) continue;
        // Collisione cerchio-rettangolo, come nella prova con una ciambella.
        const glm::vec2 nearest = glm::clamp(donut.position, center-halfSize, center+halfSize);
        const glm::vec2 distance = donut.position-nearest;
        if (glm::dot(distance,distance) <= donut.radius*donut.radius)
            donut.collected = true;
    }
}
