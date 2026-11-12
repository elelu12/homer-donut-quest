// ============================================================================
// Geometry.h - GUIDA DIDATTICA
// Interfaccia della geometria: incapsula vector CPU, VAO, VBO e operazioni di caricamento e disegno.
// ============================================================================

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Geometry
{
// PUBLIC: operazioni che il resto del programma puo' chiedere a una geometria.
// Il chiamante non deve conoscere gli identificatori OpenGL interni.
public:
    // Costruttore predefinito: i campi ricevono i valori iniziali dichiarati sotto.
    Geometry() = default;

    // Vietiamo la copia: due oggetti non devono eliminare gli stessi VAO/VBO.
    Geometry(const Geometry&) = delete;
    Geometry& operator=(const Geometry&) = delete;

    // Lo spostamento trasferisce la proprieta' delle risorse senza duplicarle.
    Geometry(Geometry&& other) noexcept;
    Geometry& operator=(Geometry&& other) noexcept;

    // Distruttore: libera le risorse GPU quando l'oggetto termina la sua vita.
    ~Geometry();

    // Memorizza sulla CPU posizioni, colori e tipo di primitiva.
    void setData(
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec4>& colors,
        GLenum primitiveType
    );

    // Crea VAO/VBO e trasferisce i vector CPU alla GPU.
    void upload(bool dynamic = false);
    // Aggiorna le posizioni di una geometria gia' caricata.
    void updatePositions(const std::vector<glm::vec3>& newPositions);
    // Aggiorna i colori dei vertici.
    void updateColors(const std::vector<glm::vec4>& newColors);
    // Disegna usando il VAO e il tipo di primitiva di questa istanza.
    void draw() const;
    // Elimina esplicitamente le risorse OpenGL possedute.
    void destroy();

    // Restituisce quanti vertici sono presenti nel vector delle posizioni.
    int vertexCount() const
    {
        return static_cast<int>(m_positions.size());
    }

// PRIVATE: dati e risorse posseduti da questa singola Geometry.
// Ogni istanza mantiene i propri vector CPU e i propri identificatori GPU.
private:
    // Coordinate dei vertici nella memoria CPU.
    std::vector<glm::vec3> m_positions;
    // Colori RGBA, uno per ciascun vertice.
    std::vector<glm::vec4> m_colors;

    // VAO: conserva la configurazione degli attributi del vertice.
    GLuint m_VAO = 0;
    // VBO GPU che memorizza le coordinate.
    GLuint m_VBO_positions = 0;
    // VBO GPU che memorizza i colori.
    GLuint m_VBO_colors = 0;

    // Stabilisce come OpenGL interpreta la sequenza di vertici.
    GLenum m_primitiveType = GL_TRIANGLES;
    // Indica se upload() ha gia' creato le risorse GPU.
    bool m_uploaded = false;
};
