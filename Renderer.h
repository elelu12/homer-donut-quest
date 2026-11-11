// ============================================================================
// Renderer.h - GUIDA DIDATTICA
// Interfaccia del renderer: pulisce il framebuffer, sceglie Fill/Wireframe e disegna gli oggetti.
// ============================================================================

#pragma once

#include <glm/glm.hpp>

class Geometry;
class Scene;

class Renderer
{
// PUBLIC: operazioni con cui il main controlla il disegno.
public:
    // Imposta il colore di pulizia e cancella il framebuffer.
    void beginFrame(const glm::vec4& clearColor) const;
    // Alterna visualizzazione piena (GL_FILL) e bordi (GL_LINE).
    void setWireframe(bool enabled) const;
    // Disegna una singola Geometry delegandole la draw call.
    void draw(const Geometry& geometry) const;
    // Attraversa tutte le Geometry contenute nella Scene.
    void drawScene(const Scene& scene) const;
};
