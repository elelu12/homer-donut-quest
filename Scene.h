// ============================================================================
// Scene.h - GUIDA DIDATTICA
// Contenitore delle Geometry: usa std::vector e offre accesso agli oggetti senza eseguire il rendering.
// ============================================================================

#pragma once

#include "Geometry.h"
#include "MeshData.h"
#include <vector>
#include <cstddef>

class Scene
{
// PUBLIC: inserimento, accesso e consultazione delle geometrie.
public:
    // Crea e carica una Geometry; restituisce il suo indice nella scena.
    std::size_t add(const MeshData& data, bool dynamic = false);

    // Accesso modificabile: consente, ad esempio, updatePositions().
    Geometry& operator[](std::size_t index)
    {
        return m_objects[index];
    }

    // Accesso in sola lettura per una Scene costante.
    const Geometry& operator[](std::size_t index) const
    {
        return m_objects[index];
    }

    // Espone il vector senza copiarlo e senza permettere modifiche.
    const std::vector<Geometry>& objects() const
    {
        return m_objects;
    }

    // Numero di oggetti presenti nella scena.
    std::size_t size() const
    {
        return m_objects.size();
    }

    // Svuota la scena: i distruttori delle Geometry liberano VAO e VBO.
    void clear();

// PRIVATE: contenitore effettivo degli oggetti della scena.
private:
    // Ogni elemento rappresenta una geometria distinta.
    std::vector<Geometry> m_objects;
};
