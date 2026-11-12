#include "Game.h"
#include <glm/common.hpp>

void Game::update(glm::vec2 direction, float deltaTime)
{
    m_player.update(direction, deltaTime);
    if (m_collected) return;

    // Collisione cerchio-rettangolo: punto del rettangolo di Homer
    // più vicino al centro della ciambella. Il foro non conta per il pickup.
    const glm::vec2 halfSize = m_player.halfSize();
    const glm::vec2 center = m_player.position();
    const glm::vec2 nearest = glm::clamp(donutPosition(), center-halfSize, center+halfSize);
    const glm::vec2 distance = donutPosition()-nearest;
    if (glm::dot(distance,distance) <= donutRadius()*donutRadius())
        m_collected = true;
}
