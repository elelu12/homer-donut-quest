#include "Player.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

void Player::update(glm::vec2 direction, float deltaTime)
{
    // Una diagonale non deve essere più veloce di un movimento orizzontale.
    if (glm::length(direction) > 1.0f)
        direction = glm::normalize(direction);
    m_position += direction * m_speed * deltaTime;

    // Ingombro conservativo dell'intero Homer in coordinate locali,
    // inclusi mani, scarpe e capelli. La scena corrente va da -1 a +1.
    const glm::vec2 halfSize = this->halfSize();
    m_position.x = std::clamp(m_position.x, World::left + halfSize.x, World::right - halfSize.x);
    m_position.y = std::clamp(m_position.y, World::laneBottom, World::laneTop);
}

glm::mat4 Player::modelMatrix() const
{
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(m_position, 0));
    return glm::scale(model, glm::vec3(m_scale, m_scale, 1));
}
