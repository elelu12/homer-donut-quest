#include "Camera.h"
#include "World.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
void Camera::update(float playerX, int width, int height)
{
    float aspect = static_cast<float>(std::max(width,1))/std::max(height,1);
    m_halfWidth = std::min(aspect, (World::right-World::left)*0.5f);
    m_halfHeight = m_halfWidth/aspect;
    m_x = std::clamp(playerX,World::left+m_halfWidth,World::right-m_halfWidth);
}
glm::mat4 Camera::view() const
{
    return glm::translate(glm::mat4(1),glm::vec3(-m_x,0,0));
}
glm::mat4 Camera::projection() const
{
    return glm::ortho(-m_halfWidth,m_halfWidth,-m_halfHeight,m_halfHeight,-1.0f,1.0f);
}
