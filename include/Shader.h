// ============================================================================
// Shader.h - GUIDA DIDATTICA
// Interfaccia che incapsula l identificatore del programma shader OpenGL.
// ============================================================================

#pragma once

#include <glad/glad.h>

class Shader
{
// PUBLIC: caricare, attivare e rilasciare un programma GLSL.
public:
    // Costruttore: il programma inizialmente non esiste (id = 0).
    Shader() = default;
    // Distruttore: richiama la pulizia delle risorse.
    ~Shader();

    // Legge, compila e collega gli shader dai file indicati.
    bool load(const char* vertexShaderFile, const char* fragmentShaderFile);
    // Rende attivo questo programma GLSL per le draw call successive.
    void use() const;
    // Elimina il programma quando non serve piu'.
    void destroy();

    // Permette di leggere l'identificatore senza modificarlo.
    GLuint id() const
    {
        return m_programId;
    }

// PRIVATE: identificatore del programma OpenGL posseduto.
private:
    // 0 indica che nessun programma e' attualmente caricato.
    GLuint m_programId = 0;
};
