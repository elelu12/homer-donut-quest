// ============================================================================
// ShapeGenerator.h - GUIDA DIDATTICA
// Interfaccia del generatore geometrico: produce MeshData senza creare risorse GPU.
// ============================================================================

#pragma once

#include "MeshData.h"

// ============================================================================
// ShapeGenerator
// Costruisce le forme sulla CPU. Nessuna chiamata OpenGL in questa classe.
//
// Genera triangolo, cerchio/ellisse e cuore parametrico.
// ============================================================================
class ShapeGenerator
{
// PUBLIC: funzioni statiche chiamabili senza creare un oggetto ShapeGenerator.
public:
    // Genera tre posizioni e tre colori sulla CPU e restituisce MeshData.
    // Ogni parametro e' un colore RGBA passato per riferimento costante.

    // riceve 3 colori, uno per ogni vertice del triangolo
    static MeshData createTriangle(
        const glm::vec4& color1,
        const glm::vec4& color2,
        const glm::vec4& color3
    );

    static MeshData createCircle(
        float cx,
        float cy,
        float radiusX,
        float radiusY,
        int segments,
        const glm::vec4& centerColor,
        const glm::vec4& borderColor
    );

    static MeshData createHeart(
        float cx,
        float cy,
        float scale,
        int segments,
        const glm::vec4& color
    );
};
