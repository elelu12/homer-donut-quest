// ============================================================================
// Gui.cpp - GUIDA DIDATTICA
// Dear ImGui: inizializzazione, costruzione dei widget e disegno della GUI sopra la scena.
// ============================================================================

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Gui.h"

// Da chiamare una sola volta dopo GLFW e GLAD. I backend collegano Dear ImGui a finestra/input e rendering OpenGL.
void Gui::initialize(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

// Da chiamare ogni iterazione prima dei widget: prepara un nuovo frame Dear ImGui.
void Gui::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

// Costruisce i widget. ColorEdit3 riceve l indirizzo del canale R; Checkbox riceve l indirizzo del bool.
void Gui::draw()
{
    ImGui::Begin("Controlli");

    ImGui::Text("Colore dello sfondo");
    ImGui::ColorEdit3(
        "Background",
        &m_clearColor.r
    );

    ImGui::Separator();

    ImGui::Text("Modalita' di visualizzazione");
    ImGui::Checkbox(
        "Wireframe",
        &m_wireframe
    );

    ImGui::End();
}

// Invia alla GPU i comandi grafici dei pannelli dopo il disegno della scena.
void Gui::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Chiude i backend e distrugge il contesto ImGui prima della chiusura di GLFW.
void Gui::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// Restituisce l'azione richiesta; il pannello non modifica direttamente il gioco.
bool Gui::drawCollection(int collected, int total, bool hit, int score, bool beerCollected)
{
    ImGui::SetNextWindowPos(ImVec2(12, 12), ImGuiCond_FirstUseEver);
    ImGui::Begin("Homer - raccolta", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Ciambelle: %d / %d", collected, total);
    ImGui::Text("Punti: %d", score);
    if (beerCollected) ImGui::TextUnformatted("Duff raccolta: +2 punti bonus!");
    ImGui::TextUnformatted("Muoviti con WASD o le frecce");
    if (total > 0 && collected == total)
        ImGui::TextUnformatted("Tutte raccolte! Obiettivo completato.");
    else if (collected > 0)
        ImGui::TextUnformatted("Continua a cercare le ciambelle!");
    if (hit) ImGui::TextUnformatted("Broccolo! Torni alla partenza, ciambelle conservate.");
    bool reset = ImGui::Button("Ricomincia");
    ImGui::End();
    return reset;
}
