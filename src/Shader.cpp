// ============================================================================
// Shader.cpp - GUIDA DIDATTICA
// Gestione del programma shader: caricamento, attivazione e rilascio.
// ============================================================================

#include "Shader.h"
#include "ShaderMaker.h"

// Il distruttore libera il programma OpenGL.
Shader::~Shader()
{
    destroy();
}

// Carica il programma GLSL e comunica il successo tramite bool.
bool Shader::load(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    destroy();

    m_programId = ShaderMaker::createProgram(
        const_cast<char*>(vertexShaderFile),
        const_cast<char*>(fragmentShaderFile)
    );

    return m_programId != 0;
}

// Attiva il programma shader per le draw call successive.
void Shader::use() const
{
    glUseProgram(m_programId);
}

// Elimina il programma solo se l identificatore e valido.
void Shader::destroy()
{
    if (m_programId != 0)
    {
        glDeleteProgram(m_programId);
        m_programId = 0;
    }
}
