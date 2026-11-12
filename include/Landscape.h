#pragma once
#include <cstddef>
class Scene;
class Renderer;
class Shader;
class Landscape
{
public:
    void create(Scene& scene);
    void draw(const Scene& scene, const Renderer& renderer, const Shader& shader) const;
private:
    std::size_t m_geometry = 0;
};
