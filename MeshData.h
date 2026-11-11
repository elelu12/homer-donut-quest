// ============================================================================
// MeshData.h - GUIDA DIDATTICA
// Struttura dati lato CPU: contiene i vector delle posizioni e dei colori e il tipo di primitiva.
// ============================================================================

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// ============================================================================
// MeshData
// Contenitore dei dati geometrici sulla CPU.
// ============================================================================
// struct: per impostazione predefinita i campi sono pubblici.
// E' un semplice pacchetto di dati, non gestisce risorse GPU.
struct MeshData
{
    // Coordinate (x,y,z) dei vertici, in ordine di disegno.
    std::vector<glm::vec3> positions;
    // Colore (r,g,b,a) corrispondente a ciascuna posizione.
    std::vector<glm::vec4> colors;
    // Tipo di primitiva usato da glDrawArrays (default: triangoli).
    GLenum primitiveType = GL_TRIANGLES;
};
