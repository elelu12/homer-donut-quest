// ============================================================================
// Scene.cpp - GUIDA DIDATTICA
// Inserisce una geometria nella scena e restituisce il suo indice nel vector.
// ============================================================================

#include "Scene.h"
#include <utility>

// Riceve i dati CPU per riferimento costante (senza copiarli come parametro). Crea una Geometry locale, ne carica i buffer e trasferisce la proprieta al vector tramite std::move. Il valore restituito e un indice, NON un VAO.
std::size_t Scene::add(const MeshData& data, bool dynamic)
{
    Geometry geometry;

    geometry.setData(
        data.positions,
        data.colors,
        data.primitiveType
    );

    geometry.upload(dynamic);

    m_objects.push_back(std::move(geometry));

    return m_objects.size() - 1;
}

// Svuota il vector; i distruttori delle Geometry liberano VAO e VBO quando il contesto OpenGL e ancora attivo.
void Scene::clear()
{
    m_objects.clear();
}
