#include "Donut.h"
#include "Scene.h"
#include "Renderer.h"
#include "Shader.h"
#include "MeshData.h"
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

void Donut::create(Scene& scene)
{
    MeshData mesh;
    constexpr float pi = 3.14159265359f;
    const glm::vec4 ink(0.07f, 0.055f, 0.055f, 1);
    auto vertex = [&](glm::vec2 p, glm::vec4 color) {
        mesh.positions.emplace_back(p, 0);
        mesh.colors.push_back(color);
    };
    auto triangle = [&](glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec4 color) {
        vertex(a, color); vertex(b, color); vertex(c, color);
    };
    // Anelli triangolati: il bordo interno segue un contorno indipendente.
    // Le fasce della glassa hanno la stessa ondulazione, come nel riferimento.
    auto ring = [&](float inner, float outer, float wave, glm::vec4 color,
                    glm::vec2 offset = glm::vec2(0)) {
        auto point = [&](float angle, bool outside) {
            float radius = outside
                ? outer + wave * (std::sin(7 * angle + 0.6f)
                                  + 0.45f * std::sin(11 * angle - 0.5f))
                : inner + 0.014f * std::sin(5 * angle + 0.5f);
            return offset + radius * glm::vec2(std::cos(angle), std::sin(angle));
        };
        for (int i = 0; i < 192; ++i) {
            float a = 2 * pi * i / 192;
            float b = 2 * pi * (i + 1) / 192;
            triangle(point(a, false), point(a, true), point(b, true), color);
            triangle(point(a, false), point(b, true), point(b, false), color);
        }
    };
    ring(0.285f, 1.0f, 0.009f, ink);
    ring(0.31f, 0.979f, 0.009f, {0.77f, 0.57f, 0.35f, 1});
    ring(0.33f, 0.96f, 0.009f, {0.87f, 0.70f, 0.48f, 1}, {-0.008f, 0.008f});
    // Bordo nero, base rosa scura, fascia chiara e superficie rosa.
    ring(0.365f, 0.936f, 0.025f, ink);
    ring(0.38f, 0.919f, 0.025f, {0.80f, 0.23f, 0.49f, 1});
    ring(0.39f, 0.865f, 0.024f, {0.97f, 0.60f, 0.74f, 1}, {-0.018f, 0.028f});
    ring(0.41f, 0.80f, 0.025f, {0.92f, 0.39f, 0.62f, 1}, {-0.008f, 0.008f});

    const glm::vec4 colors[] = {
        {0.98f, 0.91f, 0.59f, 1}, {0.33f, 0.78f, 0.88f, 1},
        {0.30f, 0.76f, 0.49f, 1}, {1, 0.96f, 0.89f, 1},
        {0.90f, 0.60f, 0.64f, 1}
    };
    
    // Piccole ellissi ruotate, triangolate come i cerchi del laboratorio.
    auto sprinkle = [&](glm::vec2 center, float angle, float sx, float sy, glm::vec4 color) {
        auto point = [&](float t) {
            glm::vec2 p(sx * std::cos(t), sy * std::sin(t));
            return center + glm::vec2(std::cos(angle)*p.x - std::sin(angle)*p.y,
                                      std::sin(angle)*p.x + std::cos(angle)*p.y);
        };
        for (int j = 0; j < 12; ++j)
            triangle(center, point(2*pi*j/12), point(2*pi*(j+1)/12), color);
    };

    for (int i = 0; i < 34; ++i) {
        int row = i / 17;
        int index = i % 17;
        float a = 2*pi*(index + row*0.47f)/17 + 0.035f*std::sin(i*3.1f); // come posizionare gli zuccherini (2 corone sfalsate)
        float radius = (row == 0 ? 0.53f : 0.77f) + 0.015f*std::sin(i*2.3f); // distanza dal centro
        float angle = i * 2.17f;
        float length = 0.049f + 0.008f*std::sin(i*1.7f); // per non fare tutti gli zuccherini uguali
        glm::vec2 center = radius * glm::vec2(std::cos(a), std::sin(a)); // trasformiamo raggio e anfolo in coordinate usando la formula delle coordinate polari
        sprinkle(center, angle, length + 0.008f, 0.020f, ink);
        sprinkle(center, angle, length, 0.011f, colors[i % 5]);
    }
    m_geometry = scene.add(mesh);
}

void Donut::draw(const Scene& scene, const Renderer& renderer,
                 const Shader& shader, const glm::mat4& transform) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader.id(), "model"),
                       1, GL_FALSE, glm::value_ptr(transform));
    renderer.draw(scene[m_geometry]);
}
