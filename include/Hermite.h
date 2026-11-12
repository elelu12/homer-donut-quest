#pragma once
#include <glm/glm.hpp>

// Base cubica condivisa da lattina e broccolo: u varia tra 0 e 1.
inline glm::vec2 hermite(glm::vec2 p0, glm::vec2 p1,
                         glm::vec2 t0, glm::vec2 t1, float u)
{
    float u2=u*u, u3=u2*u;
    return (2*u3-3*u2+1)*p0 + (u3-2*u2+u)*t0
         + (-2*u3+3*u2)*p1 + (u3-u2)*t1;
}
