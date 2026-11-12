// ============================================================================
// Geometry.cpp - GUIDA DIDATTICA
// Gestione delle risorse OpenGL: upload dei vector nei VBO, configurazione VAO, aggiornamento e distruzione.
// ============================================================================

#include "Geometry.h"
#include <utility>

// Costruttore di spostamento: trasferisce la proprieta delle risorse senza duplicare identificatori GPU.
Geometry::Geometry(Geometry&& other) noexcept
{
    *this = std::move(other);
}

// Assegnazione per spostamento: libera le vecchie risorse e azzera gli identificatori della sorgente per evitare doppie cancellazioni.
Geometry& Geometry::operator=(Geometry&& other) noexcept
{
    if (this != &other)
    {
        destroy();

        m_positions = std::move(other.m_positions);
        m_colors = std::move(other.m_colors);

        m_VAO = other.m_VAO;
        m_VBO_positions = other.m_VBO_positions;
        m_VBO_colors = other.m_VBO_colors;

        m_primitiveType = other.m_primitiveType;
        m_uploaded = other.m_uploaded;

        other.m_VAO = 0;
        other.m_VBO_positions = 0;
        other.m_VBO_colors = 0;
        other.m_uploaded = false;
    }

    return *this;
}

// Distruttore RAII: rilascia automaticamente le risorse GPU.
Geometry::~Geometry()
{
    destroy();
}

// Copia i vector CPU e memorizza il tipo di primitiva. Non esegue ancora upload sulla GPU.
void Geometry::setData(
    const std::vector<glm::vec3>& positions,
    const std::vector<glm::vec4>& colors,
    GLenum primitiveType)
{
    m_positions = positions;
    m_colors = colors;
    m_primitiveType = primitiveType;
}

// Crea VAO e due VBO. Il VAO registra la configurazione degli attributi, mentre i VBO contengono i dati.
void Geometry::upload(bool dynamic)
{
    destroy();

    const GLenum usage = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

    // Genera l identificatore del VAO.
    glGenVertexArrays(1, &m_VAO);
    // Rende corrente il VAO per registrare gli attributi.
    glBindVertexArray(m_VAO);

    // Genera l identificatore di un buffer OpenGL.
    glGenBuffers(1, &m_VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_positions);
    // Alloca memoria GPU e copia i dati dalla CPU.
    glBufferData(
        GL_ARRAY_BUFFER,
        m_positions.size() * sizeof(glm::vec3),
        m_positions.data(),
        usage
    );

    // Descrive formato, stride e offset dell attributo nel VBO corrente.
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec3),
        reinterpret_cast<void*>(0)
    );
    // Abilita la location dell attributo nel VAO.
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_colors);
    glBufferData(
        GL_ARRAY_BUFFER,
        m_colors.size() * sizeof(glm::vec4),
        m_colors.data(),
        usage
    );

    glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec4),
        reinterpret_cast<void*>(0)
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_uploaded = true;
}

// Aggiorna le posizioni CPU e il relativo VBO; la dimensione caricata non deve superare la memoria precedentemente allocata.
void Geometry::updatePositions(const std::vector<glm::vec3>& newPositions)
{
    m_positions = newPositions;

    if (!m_uploaded)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_positions);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        m_positions.size() * sizeof(glm::vec3),
        m_positions.data()
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Aggiorna i colori CPU e il relativo VBO; richiede dimensione compatibile con la memoria GPU allocata.
void Geometry::updateColors(const std::vector<glm::vec4>& newColors)
{
    m_colors = newColors;

    if (!m_uploaded)
        return;

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO_colors);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        m_colors.size() * sizeof(glm::vec4),
        m_colors.data()
    );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Attiva il VAO e invia una draw call: il tipo di primitiva e il numero di vertici sono conservati nell oggetto.
void Geometry::draw() const
{
    if (!m_uploaded)
        return;

    glBindVertexArray(m_VAO);
    // Disegna i vertici usando la primitiva configurata.
    glDrawArrays(m_primitiveType, 0, vertexCount());
    glBindVertexArray(0);
}

// Libera i VBO e il VAO se presenti; azzera gli identificatori per evitare doppie eliminazioni.
void Geometry::destroy()
{
    if (m_VBO_positions != 0)
    {
        glDeleteBuffers(1, &m_VBO_positions);
        m_VBO_positions = 0;
    }

    if (m_VBO_colors != 0)
    {
        glDeleteBuffers(1, &m_VBO_colors);
        m_VBO_colors = 0;
    }

    if (m_VAO != 0)
    {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }

    m_uploaded = false;
}
