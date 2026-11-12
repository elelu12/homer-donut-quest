// ============================================================================
// ShapeGenerator.cpp - GUIDA DIDATTICA
// Costruzione del triangolo sulla CPU: associa una posizione e un colore a ogni vertice.
// ============================================================================

#include "ShapeGenerator.h"
#include <cmath>

constexpr float PI = 3.14159265358979323846f;
// La funzione restituisce per valore un MeshData. I tre vertici sono in coordinate locali e hanno colori corrispondenti.
MeshData ShapeGenerator::createTriangle(
    const glm::vec4& color1,
    const glm::vec4& color2,
    const glm::vec4& color3)
{
    MeshData data;

    // Inseriamo i vertici uno alla volta: push_back aggiunge un elemento
    // alla fine del vector delle posizioni.
    // P0: vertice inferiore sinistro.
    data.positions.push_back(glm::vec3(-0.6f, -0.5f, 0.0f));

    // P1: vertice inferiore destro.
    data.positions.push_back(glm::vec3( 0.6f, -0.5f, 0.0f));

    // P2: vertice superiore.
    data.positions.push_back(glm::vec3( 0.0f,  0.6f, 0.0f));

    // Ogni colore ha lo stesso indice del vertice corrispondente.
    data.colors.push_back(color1);  // Colore del vertice P0.
    data.colors.push_back(color2);  // Colore del vertice P1.
    data.colors.push_back(color3);  // Colore del vertice P2.

    data.primitiveType = GL_TRIANGLES;

    return data;
}

MeshData ShapeGenerator::createCircle(
    float cx,
    float cy,
    float radiusX,
    float radiusY,
    int segments,
    const glm::vec4& centerColor,
    const glm::vec4& borderColor
)
{
    MeshData data;
    
    float step = 2.0f*PI/static_cast<float>(segments);
    data.positions.push_back(glm::vec3(cx, cy, 0.0f));
    data.colors.push_back(centerColor);

    for(int i = 0; i <= segments; i++)
    {
        float theta = static_cast<float>(i)*step;
        float x = cx + radiusX * std::cos(theta);
        float y = cy + radiusY * std::sin(theta);

        data.positions.push_back(glm::vec3(x, y, 0.0f));
        data.colors.push_back(borderColor);

    }
    data.primitiveType = GL_TRIANGLE_FAN;

    return data;
}

// Cuore parametrico: formule di OpenGL Parte 2, pagina 3.
MeshData ShapeGenerator::createHeart(
    float cx,
    float cy,
    float scale,
    int segments,
    const glm::vec4& color)
{
    MeshData data;
    data.primitiveType = GL_TRIANGLE_FAN;

    if (segments < 3)
        return data;

    // Centro + punti del bordo + punto di chiusura.
    data.positions.reserve(segments + 2);
    data.colors.reserve(segments + 2);

    data.positions.push_back(glm::vec3(cx, cy, 0.0f));
    data.colors.push_back(color);

    float step = 2.0f * PI / static_cast<float>(segments);

    for (int i = 0; i <= segments; i++)
    {
        float t = static_cast<float>(i) * step;

        // Ripete esattamente il primo punto per chiudere il bordo.
        if (i == segments)
            t = 0.0f;

        // Formule della prof.
        float x = 16.0f * std::pow(std::sin(t), 3);
        float y = 13.0f * std::cos(t)
                - 5.0f * std::cos(2.0f * t)
                - 2.0f * std::cos(3.0f * t)
                - std::cos(4.0f * t);

        // Ridimensionamento e posizionamento nella scena.
        data.positions.push_back(
            glm::vec3(cx + scale * x, cy + scale * y, 0.0f)
        );
        data.colors.push_back(color);
    }

    return data;
}
