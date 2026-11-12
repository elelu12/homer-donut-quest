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
    m_lives = 3;
    m_won = false;
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

glm::vec2 Game::broccoliPosition(int index) const
{
    const float centers[] = {2.4f,4.4f,6.2f,7.55f};
    // Corsie alternate: si possono aggirare usando anche su/giu'.
    float y = index%2 == 0 ? -0.30f : -0.78f;
    return {centers[index] + 0.30f * std::sin(m_time * 1.2f + index), y};
}

void Game::update(glm::vec2 direction, float deltaTime)
{
    if (won() || gameOver()) return;
    m_time += deltaTime;
    m_hitTimer = std::max(0.0f, m_hitTimer-deltaTime);
    m_player.update(direction, deltaTime);
    // Un solo danno per contatto, anche se due ostacoli si sovrapponessero.
    for (int i=0; i<obstacleCount(); ++i) {
        const glm::vec2 separation = glm::abs(m_player.position()-broccoliPosition(i));
        const glm::vec2 reach = m_player.halfSize()+broccoliHalfSize();
        if (m_hitTimer <= 0 && separation.x <= reach.x && separation.y <= reach.y) {
            --m_lives;
            if (!gameOver()) m_player = Player{};
            m_hitTimer = 1.5f;
            return;
        }
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
    const glm::vec2 goalDistance = glm::abs(center-goalPosition());
    if (collectedCount() == totalCount() && goalDistance.x < 0.18f && goalDistance.y < 0.13f)
        m_won = true;

}
