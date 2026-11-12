#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
    void update(float playerX, int width, int height);
    glm::mat4 view() const;
    glm::mat4 projection() const;
private:
    float m_x = 1;
    float m_halfWidth = 1;
    float m_halfHeight = 1;
};
