#pragma once
#include <cstddef>
#include <glm/glm.hpp>
class Scene;
class Renderer;
class Shader;

// Lattina Duff: contorno Hermite campionato e dettagli geometrici.
class Beer
{
public:
    void create(Scene& scene);
    void draw(const Scene& scene, const Renderer& renderer, const Shader& shader, const glm::mat4& transform) const; // responsabile del rendering della lattina

private:
    std::size_t m_geometry = 0;
};
