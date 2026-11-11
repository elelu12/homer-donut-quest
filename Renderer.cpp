// ============================================================================
// Renderer.cpp - GUIDA DIDATTICA
// Rendering: attraversa la scena e delega a ciascuna Geometry la propria draw call.
// ============================================================================

#include "Renderer.h"
#include <glad/glad.h>
#include "Geometry.h"
#include "Scene.h"

// glClearColor imposta il colore usato da glClear per cancellare il framebuffer.
void Renderer::beginFrame(const glm::vec4& clearColor) const
{
    glClearColor(
        clearColor.r,
        clearColor.g,
        clearColor.b,
        clearColor.a
    );

    glClear(GL_COLOR_BUFFER_BIT);
}

// L operatore ternario seleziona GL_LINE o GL_FILL. GL_POINTS non e influenzato da glPolygonMode.
void Renderer::setWireframe(bool enabled) const
{
    glPolygonMode(
        GL_FRONT_AND_BACK,
        enabled ? GL_LINE : GL_FILL
    );
}

// Delega il disegno alla singola Geometry: il Renderer non conosce il VAO dell oggetto.
void Renderer::draw(const Geometry& geometry) const
{
    geometry.draw();
}

// Range-based for: per ogni Geometry nella Scene, ottiene un riferimento costante e chiama draw senza copiare oggetti.
void Renderer::drawScene(const Scene& scene) const
{
    for (const Geometry& geometry : scene.objects())
        draw(geometry);
}
