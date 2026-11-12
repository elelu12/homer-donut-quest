#include "Beer.h"
#include "Scene.h"
#include "Renderer.h"
#include "Shader.h"
#include "MeshData.h"
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <vector>

#include "Hermite.h"

void Beer::create(Scene& scene)
{
    MeshData mesh;
    const glm::vec4 ink(0.06f, 0.055f, 0.055f, 1);
    const glm::vec4 silver(0.80f, 0.82f, 0.82f, 1);
    const glm::vec4 red(0.73f, 0.15f, 0.17f, 1);
    const glm::vec4 gold(0.66f, 0.39f, 0.18f, 1);
    const glm::vec4 label(0.93f, 0.92f, 0.87f, 1);
    auto triangle = [&](glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec4 color) {
        for (auto p : {a,b,c}) {
            mesh.positions.emplace_back(p, 0);
            mesh.colors.push_back(color);
        }
    };
    auto polygon = [&](const std::vector<glm::vec2>& points, glm::vec2 center, glm::vec4 color) {
        for (std::size_t i=0; i<points.size(); ++i)
            triangle(center, points[i], points[(i+1)%points.size()], color);
    };
    auto ellipse = [&](glm::vec2 center, glm::vec2 radius, glm::vec4 color) {
        std::vector<glm::vec2> points;
        for (int i=0; i<64; ++i) {
            float a = 6.2831853f*i/64;
            points.push_back(center + radius*glm::vec2(std::cos(a), std::sin(a)));
        }
        polygon(points, center, color);
    };
    auto stroke = [&](glm::vec2 a, glm::vec2 b, float width, glm::vec4 color) {
        glm::vec2 d = b-a;
        glm::vec2 n = glm::normalize(glm::vec2(-d.y,d.x))*width*0.5f;
        triangle(a+n,a-n,b+n,color); triangle(a-n,b-n,b+n,color);
        ellipse(a, glm::vec2(width*0.5f), color);
        ellipse(b, glm::vec2(width*0.5f), color);
    };
    // Profilo chiuso convesso: campionamento di otto tratti di Hermite.
    // La triangolazione a ventaglio è adatta a questo contorno, non a ogni curva.
    const std::vector<glm::vec2> points = {
        {-0.43f,-0.78f}, {0,-0.94f}, {0.43f,-0.78f}, {0.43f,0.66f},
        {0.31f,0.83f}, {0,0.89f}, {-0.31f,0.83f}, {-0.43f,0.66f}
    };
    const std::vector<glm::vec2> tangents = {
        {0,-0.28f}, {0.58f,0}, {0,0.28f}, {0,0.28f},
        {-0.25f,0.12f}, {-0.40f,0}, {-0.25f,-0.12f}, {0,-0.28f}
    };
    std::vector<glm::vec2> contour;
    for (std::size_t i=0; i<points.size(); ++i) {
        auto next = (i+1)%points.size();
        for (int j=0; j<24; ++j)
            contour.push_back(hermite(points[i],points[next],tangents[i],tangents[next],j/24.0f));
    }
    polygon(contour, {0,0}, ink);
    for (auto& p : contour) p *= glm::vec2(0.96f,0.98f);
    polygon(contour, {0,0}, silver);

    // Fascia cilindrica: bordo superiore e inferiore sono archi paralleli.
    // Triangoliamo ogni striscia direttamente: nessun ventaglio su contorni concavi.
    auto curvedBand = [&](float halfWidth, float top, float bottom, float sag,
                          glm::vec4 color) {
        auto point = [&](float x, float y) {
            float u = x / halfWidth;
            return glm::vec2(x, y - sag * (1.0f-u*u));
        };
        for (int i=0; i<64; ++i) {
            float x0 = -halfWidth + 2*halfWidth*i/64;
            float x1 = -halfWidth + 2*halfWidth*(i+1)/64;
            triangle(point(x0,top),point(x0,bottom),point(x1,top),color);
            triangle(point(x1,top),point(x0,bottom),point(x1,bottom),color);
        }
    };
    curvedBand(0.425f, 0.46f, -0.65f, 0.12f, ink);
    curvedBand(0.411f, 0.442f, -0.632f, 0.12f, red);
    // Fascia dorata con la stessa curvatura dell'etichetta.
    curvedBand(0.425f, 0.46f, 0.27f, 0.12f, ink);
    curvedBand(0.411f, 0.442f, 0.288f, 0.12f, gold);
    ellipse({0,0.245f},{0.066f,0.068f},ink);
    ellipse({0,0.245f},{0.052f,0.054f},red);
    // Anche il pannello chiaro si avvolge attorno al cilindro.
    curvedBand(0.34f, 0.035f, -0.36f, 0.035f, ink);
    curvedBand(0.323f, 0.018f, -0.343f, 0.035f, label);

    // Scritta Duff stilizzata con tratti geometrici (nessun font o texture).
    stroke({-0.275f,-0.39f},{-0.275f,0.12f},0.055f,ink);
    glm::vec2 previous(-0.275f,0.12f);
    for(int i=1;i<=32;++i) {
        float a = 3.14159265f*i/32;
        glm::vec2 p(-0.275f+0.15f*std::sin(a),-0.135f+0.255f*std::cos(a));
        stroke(previous,p,0.052f,ink); previous=p;
    }
    stroke({-0.055f,-0.13f},{-0.055f,-0.28f},0.048f,ink);
    stroke({-0.055f,-0.28f},{0.005f,-0.30f},0.048f,ink);
    stroke({0.005f,-0.30f},{0.035f,-0.12f},0.048f,ink);
    for(float x : {0.13f,0.265f}) {
        stroke({x-0.025f,-0.37f},{x,0.09f},0.05f,ink);
        stroke({x,0.09f},{x+0.035f,0.12f},0.05f,ink);
        stroke({x+0.035f,0.12f},{x+0.055f,0.07f},0.05f,ink);
        stroke({x-0.055f,-0.13f},{x+0.05f,-0.09f},0.042f,ink);
        stroke({x-0.025f,-0.37f},{x-0.06f,-0.39f},0.05f,ink);
    }
    // Coperchio e linguetta, sovrapposti al bordo superiore della lattina.
    ellipse({0,0.73f},{0.445f,0.18f},ink);
    ellipse({0,0.735f},{0.425f,0.159f},silver);
    ellipse({0,0.755f},{0.355f,0.104f},ink);
    ellipse({0,0.766f},{0.34f,0.088f},silver);
    ellipse({0.01f,0.735f},{0.105f,0.048f},ink);
    ellipse({0.035f,0.78f},{0.085f,0.044f},ink);
    ellipse({0.035f,0.782f},{0.064f,0.027f},silver);
    m_geometry = scene.add(mesh);
}

void Beer::draw(const Scene& scene, const Renderer& renderer,
                const Shader& shader, const glm::mat4& transform) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"model"),1,GL_FALSE,glm::value_ptr(transform));
    renderer.draw(scene[m_geometry]);
}
