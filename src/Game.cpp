#include "Game.h"
#include <glm/common.hpp>
#include <cmath>
#include <algorithm>

Game::Game()
{
    reset();
}

void Game::reset()
{
    m_beerCollected = false;
    m_time = 0;
    m_hitTimer = 0;
    m_player = Player{};
    // Cinque stati indipendenti; nessuna copia dei vertici della mesh.
    m_donuts = {
        {{1.5f,-0.55f},0.10f,0.15f,false},
        {{3.3f,-0.68f},0.10f,-0.35f,false},
        {{5.0f,-0.35f},0.10f,0.60f,false},
        {{7.0f,-0.65f},0.10f,-0.20f,false},
        {{9.1f,-0.45f},0.10f,0.40f,false}
    };
}

int Game::collectedCount() const
{
    int count = 0;
    for (const DonutInstance& donut : m_donuts)
        if (donut.collected) ++count;
    return count;
}

glm::vec2 Game::broccoliPosition() const
{
    return {4.4f + 0.65f * std::sin(m_time * 1.2f), -0.35f};
}

void Game::update(glm::vec2 direction, float deltaTime)
{
    m_time += deltaTime;
    m_hitTimer = std::max(0.0f, m_hitTimer-deltaTime);
    m_player.update(direction, deltaTime);
    // Rettangoli allineati agli assi, dimensionati in coordinate di scena.
    const glm::vec2 separation = glm::abs(m_player.position()-broccoliPosition());
    const glm::vec2 reach = m_player.halfSize()+broccoliHalfSize();
    if (m_hitTimer <= 0 && separation.x <= reach.x && separation.y <= reach.y) {
        m_player = Player{};
        m_hitTimer = 1.5f; // Feedback e breve protezione dopo il contatto.
        return;          // Nessuna raccolta nello stesso frame della collisione.
    }
    const glm::vec2 halfSize = m_player.halfSize();
    const glm::vec2 center = m_player.position();
    // Ingombro conservativo della lattina, scalato come la sua geometria.
    const glm::vec2 beerReach = halfSize + glm::vec2(0.45f,0.95f)*beerScale();
    const glm::vec2 beerDistance = glm::abs(center-beerPosition());
    if (!m_beerCollected && beerDistance.x <= beerReach.x && beerDistance.y <= beerReach.y)
        m_beerCollected = true;
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
