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
#include "Game.h"

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
bool Gui::drawCollection(const Game& game)
{
    ImGui::SetNextWindowPos(ImVec2(12, 12), ImGuiCond_FirstUseEver);
    ImGui::Begin("Homer - raccolta", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    // Cuori pixelati: ogni carattere è un quadratino, senza texture o font esterni.
    const char* pixels[] = {
        "..BBB.BBB..", ".BRRRBRRRB.", "BRRRRRRWWRB", "BRRRRRRRWRB",
        "BDRRRRRRRRB", ".BDRRRRRRB.", "..BDRRRRB..", "...BDRRB...",
        "....BDB....", ".....B....."
    };
    ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* draw = ImGui::GetWindowDrawList();
    const float pixel = 3.0f;
    for (int heart=0; heart<3; ++heart) {
        bool active = heart < game.lives();
        for (int y=0;y<10;++y) for(int x=0;x<11;++x) {
            char cell=pixels[y][x];
            if(cell=='.') continue;
            ImU32 color = IM_COL32(28,21,26,255);
            if(cell!='B') {
                color = active ? IM_COL32(237,30,48,255) : IM_COL32(75,70,76,255);
                if(active && cell=='D') color=IM_COL32(160,28,40,255);
                if(active && cell=='W') color=IM_COL32(255,239,225,255);
            }
            ImVec2 a(origin.x+heart*42+x*pixel,origin.y+y*pixel);
            draw->AddRectFilled(a,ImVec2(a.x+pixel,a.y+pixel),color);
        }
    }
    ImGui::Dummy(ImVec2(126,34));
    ImGui::Text("Ciambelle: %d / %d", game.collectedCount(), game.totalCount());
    ImGui::Text("Punti: %d", game.score());
    if (game.beerCollected()) ImGui::TextUnformatted("Duff raccolta: +2 punti bonus!");
    if (game.gameOver()) ImGui::TextUnformatted("GAME OVER - Hai finito le vite.");
    else if (game.won()) ImGui::TextUnformatted("Sei arrivato da Moe! Hai vinto!");
    else {
        ImGui::TextUnformatted("Muoviti con WASD o le frecce");
        if(game.collectedCount()==game.totalCount())
            ImGui::TextUnformatted("Ora raggiungi la porta di Moe's!");
        else ImGui::TextUnformatted("Raccogli 5 ciambelle, poi vai da Moe's.");
        if(game.hitFeedback()) ImGui::TextUnformatted("Ahi! -1 vita. Raccolta conservata.");
    }
    bool reset=ImGui::Button("Ricomincia");
    ImGui::End();
    return reset;
}
