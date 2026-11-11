// ============================================================================
// main.cpp - GUIDA DIDATTICA
// Punto di ingresso: inizializza GLFW e GLAD, crea shader e scena, avvia il ciclo di rendering e rilascia le risorse.
// ============================================================================

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "ShapeGenerator.h"
#include "Scene.h"
#include "Renderer.h"
#include "Gui.h"
#include "Input.h"
#include "Homer.h"

// Avvio del programma. Le risorse OpenGL vanno create solo dopo che esiste un contesto corrente.
int main()
{
    // ========================================================================
    // 1. GLFW
    // ========================================================================

    if (!/* Inizializza GLFW prima di creare la finestra. */
    glfwInit())
    {
        std::cout << "Errore inizializzazione GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    // ========================================================================
    // 2. FINESTRA
    // ========================================================================

    GLFWwindow* window = glfwCreateWindow(
        800,
        800,
        "OpenGL - Template classi",
        nullptr,
        nullptr
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    // ========================================================================
    // 3. GLAD
    // ========================================================================

    if (!/* Carica le funzioni OpenGL dopo avere reso corrente il contesto. */
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Errore caricamento GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 800);


    // ========================================================================
    // 4. CALLBACK
    // ========================================================================

    glfwSetKeyCallback(window, Input::keyCallback);
    glfwSetCursorPosCallback(window, Input::cursorPositionCallback);
    glfwSetFramebufferSizeCallback(window, Input::framebufferSizeCallback);


    // ========================================================================
    // 5. SHADER
    // ========================================================================

    Shader shader;

    if (!shader.load(
        "shader/vertexshaderC.glsl",
        "shader/fragmentshaderC.glsl"))
    {
        std::cout << "Errore caricamento shader" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    shader.use();


    // ========================================================================
    // 6. SCENA, RENDERER E GUI
    // ========================================================================

    Scene scene;
    Renderer renderer;
    Gui gui;

    gui.initialize(window);


    // Personaggio composto: le parti condividono geometrie e usano matrici locali.
    Homer homer;
    homer.create(scene);

    // BLENDING
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ========================================================================
    // 8. RENDER LOOP
    // ========================================================================

    // Ciclo dei frame: aggiorna i controlli, pulisce lo schermo, disegna la scena e presenta il risultato.
    while (!glfwWindowShouldClose(window))
    {
        /* Inizia il frame dell interfaccia prima di costruire i widget. */
    gui.beginFrame();
        gui.draw();

        renderer.beginFrame(gui.clearColor());
        renderer.setWireframe(gui.wireframe());

        shader.use();
        /* Il Renderer visita tutte le Geometry e ne richiama draw(). */
    homer.draw(scene, renderer, shader, glm::mat4(1.0f));

        // ImGui va disegnata in modalita' fill.
        renderer.setWireframe(false);
        /* Disegna la GUI sopra la scena OpenGL. */
    gui.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // ========================================================================
    // 9. CLEANUP
    // ========================================================================

    gui.shutdown();
    scene.clear();
    shader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
