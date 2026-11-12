#pragma once
#include <cstddef>
#include <glm/glm.hpp>
class Scene;
class Renderer;
class Shader;

// Una mesh condivisibile da tutte le future ciambelle raccoglibili.
class Donut
{
public:
    void create(Scene& scene);
    void draw(const Scene& scene, const Renderer& renderer,
              const Shader& shader, const glm::mat4& transform) const;
private:
    std::size_t m_geometry = 0;
};
