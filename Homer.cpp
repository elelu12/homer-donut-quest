#include "Homer.h"
#include "Scene.h"
#include "Renderer.h"
#include "Shader.h"
#include "ShapeGenerator.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

void Homer::create(Scene& scene)
{
    m_parts.clear();
    const glm::vec4 yellow(1.0f, 0.80f, 0.05f, 1.0f);
    const glm::vec4 white(0.98f, 0.98f, 0.94f, 1.0f);
    const glm::vec4 blue(0.25f, 0.48f, 0.72f, 1.0f);
    const glm::vec4 dark(0.12f, 0.11f, 0.12f, 1.0f);
    const glm::vec4 beard(0.72f, 0.55f, 0.34f, 1.0f);

    // Una sola geometria per colore, riutilizzata dalle parti con matrici diverse.
    auto ellipse = [&](const glm::vec4& color) {
        return scene.add(ShapeGenerator::createCircle(0, 0, 1, 1, 48, color, color));
    };
    const auto skin = ellipse(yellow);
    const auto shirt = ellipse(white);
    const auto pants = ellipse(blue);
    const auto outline = ellipse(dark);
    const auto muzzle = ellipse(beard);

    // Disegno dal fondo verso il primo piano, in coordinate locali.
    auto part = [&](std::size_t mesh, float x, float y, float sx, float sy, float angle = 0.0f) {
        m_parts.push_back({mesh, {x, y}, {sx, sy}, angle});
    };
    // Silhouette ispirata al riferimento: figura alta, pancia sporgente
    // a sinistra e un braccio alzato. Le coordinate sono locali a Homer.
    part(pants, -0.105f, -0.44f, 0.105f, 0.25f);       // gambe
    part(pants,  0.105f, -0.44f, 0.105f, 0.25f);
    part(outline, -0.14f, -0.67f, 0.15f, 0.055f);      // scarpe
    part(outline,  0.10f, -0.67f, 0.15f, 0.055f);
    part(skin, -0.28f, -0.10f, 0.07f, 0.22f, -0.08f); // braccio lungo il fianco
    part(skin, -0.30f, -0.30f, 0.075f, 0.07f);        // mano
    part(skin,  0.28f, -0.10f, 0.07f, 0.22f, 0.08f);  // braccio abbassato
    part(skin,  0.30f, -0.30f, 0.075f, 0.07f);        // mano
    part(pants, 0.0f, -0.26f, 0.225f, 0.14f);         // pantaloni
    part(shirt, -0.22f, 0.06f, 0.105f, 0.12f, -0.25f); // maniche
    part(shirt,  0.22f, 0.06f, 0.105f, 0.12f,  0.25f);
    part(shirt, 0.0f, 0.015f, 0.17f, 0.27f);            // busto
    part(shirt, -0.035f, -0.15f, 0.265f, 0.225f);       // pancia
    part(skin, 0.0f, 0.24f, 0.105f, 0.11f);            // collo
    part(skin, 0.0f, 0.39f, 0.145f, 0.235f);           // testa allungata
    part(skin, 0.14f, 0.32f, 0.05f, 0.065f);           // orecchio
    part(muzzle, -0.055f, 0.305f, 0.15f, 0.085f);      // muso
    part(outline, -0.075f, 0.285f, 0.075f, 0.008f, -0.08f); // bocca
    part(skin, -0.16f, 0.385f, 0.075f, 0.042f);       // naso
    part(shirt, -0.085f, 0.43f, 0.065f, 0.052f);      // occhi
    part(shirt,  0.025f, 0.43f, 0.065f, 0.052f);
    part(outline, -0.105f, 0.43f, 0.011f, 0.016f);    // pupille
    part(outline,  0.005f, 0.43f, 0.011f, 0.016f);
    // M continua: ogni segmento unisce esattamente due vertici successivi.
    auto hairSegment = [&](glm::vec2 a, glm::vec2 b) {
        const glm::vec2 delta = b - a;
        const glm::vec2 middle = (a + b) * 0.5f;
        part(outline, middle.x, middle.y, 0.006f, glm::length(delta) * 0.5f,
             std::atan2(-delta.x, delta.y));
    };
    hairSegment({0.085f, 0.35f}, {0.085f, 0.41f});
    hairSegment({0.085f, 0.41f}, {0.106f, 0.385f});
    hairSegment({0.106f, 0.385f}, {0.127f, 0.41f});
    hairSegment({0.127f, 0.41f}, {0.127f, 0.35f});
    part(outline, -0.02f, 0.625f, 0.065f, 0.012f, 0.35f); // capelli
    part(outline, 0.035f, 0.64f, 0.065f, 0.012f, -0.35f);
}

void Homer::draw(const Scene& scene, const Renderer& renderer, const Shader& shader,
                 const glm::mat4& transform) const
{
    // parent * traslazione * rotazione * scala: la trasformazione comune
    // agisce sull'intero personaggio, quelle locali compongono le sue parti.
    const GLint modelLocation = glGetUniformLocation(shader.id(), "model");
    for (const Part& part : m_parts)
    {
        glm::mat4 model = glm::translate(transform, glm::vec3(part.position, 0.0f));
        model = glm::rotate(model, part.angle, glm::vec3(0, 0, 1));
        model = glm::scale(model, glm::vec3(part.scale, 1.0f));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        renderer.draw(scene[part.geometry]);
    }
}
