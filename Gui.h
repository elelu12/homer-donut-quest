// ============================================================================
// Gui.h - GUIDA DIDATTICA
// Interfaccia della GUI: conserva lo stato dei controlli e offre getter al main.
// ============================================================================

#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;

// ============================================================================
// Gui
// Incapsula Dear ImGui e i parametri modificabili dall'utente.
// ============================================================================
class Gui
{
// PUBLIC: ciclo di vita dell'interfaccia e lettura dei valori scelti.
public:
    // Crea il contesto ImGui e inizializza i backend GLFW/OpenGL.
    void initialize(GLFWwindow* window);
    // Avvia la costruzione dei widget per il frame corrente.
    void beginFrame();
    // Definisce finestra, selettore colore e checkbox.
    void draw();
    // Disegna la GUI sopra la scena OpenGL.
    void render();
    // Rilascia le risorse ImGui prima di distruggere il contesto.
    void shutdown();

    // Getter: fornisce il colore al Renderer senza copiarlo.
    const glm::vec4& clearColor() const
    {
        return m_clearColor;
    }

    // Getter: restituisce lo stato della checkbox Wireframe.
    bool wireframe() const
    {
        return m_wireframe;
    }

// PRIVATE: stato dei widget, protetto dall'accesso diretto del main.
private:
    // Colore RGBA dello sfondo, modificato dal widget ColorEdit3.
    glm::vec4 m_clearColor = glm::vec4(0.0f, 0.2f, 1.0f, 1.0f);
    // false = Fill; true = Wireframe.
    bool m_wireframe = false;
};
