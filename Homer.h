#pragma once

#include <glm/glm.hpp>
#include <cstddef>
#include <vector>

class Scene;
class Shader;
class Renderer;

// Homer è assemblato da ellissi: ogni parte ha una trasformazione locale.
class Homer
{
public:
    void create(Scene& scene);
    void draw(const Scene& scene, const Renderer& renderer, const Shader& shader,
              const glm::mat4& transform) const;

private:
    struct Part
    {
        std::size_t geometry;
        glm::vec2 position;
        glm::vec2 scale;
        float angle;
    };
    std::vector<Part> m_parts;
};
