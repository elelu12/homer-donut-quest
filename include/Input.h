// ============================================================================
// Input.h - GUIDA DIDATTICA
// Dichiarazioni delle callback GLFW per tastiera, cursore e ridimensionamento.
// ============================================================================

#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Namespace: raggruppa funzioni e variabili di input senza creare una classe.
namespace Input
{
    // extern: la variabile e' definita in Input.cpp.
    glm::vec2 movementDirection(GLFWwindow* window);

    extern double mouseX;
    // Coordinata verticale del cursore, definita in Input.cpp.
    extern double mouseY;

    // Callback invocata da GLFW quando cambia lo stato di un tasto.
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // Callback invocata quando il mouse si sposta.
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    // Callback per aggiornare il viewport al ridimensionamento.
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
}
