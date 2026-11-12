// ============================================================================
// Input.cpp - GUIDA DIDATTICA
// Implementazione delle callback GLFW: eventi e viewport.
// ============================================================================

#include <glad/glad.h>
#include "Input.h"

namespace Input
{
    // Lettura continua: non dipende dalla ripetizione automatica dei tasti.
    glm::vec2 movementDirection(GLFWwindow* window)
    {
        auto down = [&](int key) { return glfwGetKey(window, key) == GLFW_PRESS; };
        glm::vec2 direction(0);
        if (down(GLFW_KEY_D) || down(GLFW_KEY_RIGHT)) direction.x += 1;
        if (down(GLFW_KEY_A) || down(GLFW_KEY_LEFT))  direction.x -= 1;
        if (down(GLFW_KEY_W) || down(GLFW_KEY_UP))    direction.y += 1;
        if (down(GLFW_KEY_S) || down(GLFW_KEY_DOWN))  direction.y -= 1;
        return direction;
    }

    double mouseX = 0.0;
    double mouseY = 0.0;

    // Gestisce il tasto ESC richiedendo la chiusura della finestra.
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        (void)scancode;
        (void)mods;

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // Aggiorna la posizione del cursore; GLFW usa l origine in alto a sinistra.
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        int width = 0;
        int height = 0;
        glfwGetFramebufferSize(window, &width, &height);

        mouseX = xpos;
        mouseY = static_cast<double>(height) - ypos;
    }

    // Aggiorna glViewport usando le dimensioni reali del framebuffer.
    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        (void)window;
        glViewport(0, 0, width, height);
    }
}
