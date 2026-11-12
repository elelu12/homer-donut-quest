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
#include "Game.h"
#include "imgui.h"
#include <algorithm>
#include "Donut.h"
#include "Beer.h"
#include "Broccoli.h"
#include <glm/gtc/matrix_transform.hpp>

//Immagina di voler allestire una mostra d'arte:
//• OpenGL è il pittore: sa solo dipingere su una tela, ma non sa dove procurarsi la tela e non sa comunicare con il pubblico.
//• GLFW è il proprietario della galleria: costruisce la stanza (la finestra), accende le luci, apre la porta e ti dice se entra qualcuno (mouse e tastiera).
//• GLAD è il fornitore: va a prendere nella cassetta degli attrezzi della scheda video tutti i pennelli e i tubetti di colore giusti (le funzioni OpenGL) e li mette in mano al pittore.

// Avvio del programma. Le risorse OpenGL vanno create solo dopo che esiste un contesto corrente.
int main()
{
    // ========================================================================
    // 1. GLFW: libreria che parla con il sistema operativo
    // ========================================================================
    // GLFW graphics Library framework 
    // gestisce la finestra e l'input

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

    // ricorda che GLFW si occupa anche di ascoltare tastiera e mouse

    // ========================================================================
    // 3. GLAD
    // ========================================================================

    // OpenGL non è una libreria con codice già pronto dentro l'eseguibile ma uno standard implementato direttamente dal driver della singola scheda video
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
    // 4. CALLBACK: è una funzione che tu scrivi, ma che passi a una libreria esterna (in questo caso GLFW)
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
    Game game;
    Homer homer;
    homer.create(scene);
    Donut donut;
    donut.create(scene);
    Beer beer;
    beer.create(scene);
    Broccoli broccoli;
    broccoli.create(scene);

    // BLENDING
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ========================================================================
    // 8. RENDER LOOP
    // ========================================================================

    // Ciclo dei frame: aggiorna i controlli, pulisce lo schermo, disegna la scena e presenta il risultato.
    double previousTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        const double now = glfwGetTime();
        // Limite per evitare salti dopo una pausa del debugger o un blocco.
        const float deltaTime = static_cast<float>(std::min(now - previousTime, 0.05));
        previousTime = now;
        /* Inizia il frame dell interfaccia prima di costruire i widget. */
    gui.beginFrame();
        gui.draw();
        glm::vec2 direction(0);
        if (!ImGui::GetIO().WantCaptureKeyboard && glfwGetWindowAttrib(window, GLFW_FOCUSED))
            direction = Input::movementDirection(window);
        game.update(direction, deltaTime);
        if (gui.drawCollection(game.collectedCount(), game.totalCount(), game.hitFeedback(), game.score(), game.beerCollected())) game.reset();

        renderer.beginFrame(gui.clearColor());
        renderer.setWireframe(gui.wireframe());

        shader.use();
        /* Il Renderer visita tutte le Geometry e ne richiama draw(). */
    homer.draw(scene, renderer, shader, game.player().modelMatrix());
        // La stessa mesh viene disegnata per ogni istanza ancora presente.
        for (const DonutInstance& instance : game.donuts()) {
            if (instance.collected) continue;
            glm::mat4 donutModel = glm::translate(glm::mat4(1.0f), glm::vec3(instance.position, 0));
            donutModel = glm::rotate(donutModel, instance.angle, glm::vec3(0, 0, 1));
            donutModel = glm::scale(donutModel, glm::vec3(instance.radius, instance.radius, 1));
            donut.draw(scene, renderer, shader, donutModel);
        }
        if (!game.beerCollected()) {
            glm::mat4 beerModel = glm::translate(glm::mat4(1.0f), glm::vec3(game.beerPosition(), 0));
            beerModel = glm::scale(beerModel, glm::vec3(game.beerScale(), 1));
            beer.draw(scene, renderer, shader, beerModel);
        }

        glm::mat4 broccoliModel = glm::translate(glm::mat4(1), glm::vec3(game.broccoliPosition(),0));
        broccoliModel = glm::scale(broccoliModel, glm::vec3(game.broccoliScale(),game.broccoliScale(),1));
        broccoli.draw(scene, renderer, shader, broccoliModel);

        // ImGui va disegnata in modalita' fill.
        renderer.setWireframe(false);
        /* Disegna la GUI sopra la scena OpenGL. */
    gui.render();

        glfwSwapBuffers(window);
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
