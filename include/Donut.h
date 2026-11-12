#pragma once
#include <cstddef>
#include <glm/glm.hpp>
class Scene;
class Renderer;
class Shader;

// Una mesh condivisibile da tutte le future ciambelle raccoglibili
// mesh = rappresentazione geometrica complessa utilizzata nella grafica 3D
// composta da un insieme di vertici, spigoli e facce
class Donut
{
public:
    void create(Scene& scene);
    void draw(const Scene& scene, const Renderer& renderer, const Shader& shader, const glm::mat4& transform) const;

private:
    std::size_t m_geometry = 0;
};
