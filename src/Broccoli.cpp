#include "Broccoli.h"
#include "Hermite.h"
#include "MeshData.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>

void Broccoli::create(Scene& scene)
{
    MeshData mesh;
    const glm::vec4 ink(0.09f,0.18f,0.11f,1);
    auto triangle = [&](glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec4 color) {
        for (auto p : {a,b,c}) { mesh.positions.emplace_back(p,0); mesh.colors.push_back(color); }
    };
    auto stem = [&](float width, glm::vec4 color) {
        triangle({-width,-0.85f},{width,-0.85f},{width*0.65f,0.25f},color);
        triangle({-width,-0.85f},{width*0.65f,0.25f},{-width*0.65f,0.25f},color);
    };
    stem(0.25f,ink); stem(0.22f,{0.46f,0.70f,0.36f,1});
    // Ogni ciuffo ha 16 punti interpolati da tratti cubici di Hermite.
    // Raggi alternati producono piccoli lobi. Le tangenti sono ricavate
    // dai punti vicini; il ventaglio riempie queste forme stellate rispetto al centro.
    auto crown = [&](glm::vec2 center, glm::vec2 scale, glm::vec4 color) {
        std::vector<glm::vec2> knots;
        for(int i=0;i<16;++i) {
            float a=6.2831853f*i/16;
            float r=(i%2==0)?1.0f:0.87f;
            knots.push_back(r*glm::vec2(std::cos(a),std::sin(a)));
        }
        for(int i=0;i<16;++i) {
            int next=(i+1)%16;
            glm::vec2 t0=(knots[next]-knots[(i+15)%16])*0.5f;
            glm::vec2 t1=(knots[(i+2)%16]-knots[i])*0.5f;
            for(int j=0;j<12;++j) {
                auto a=hermite(knots[i],knots[next],t0,t1,j/12.0f);
                auto b=hermite(knots[i],knots[next],t0,t1,(j+1)/12.0f);
                triangle(center,center+scale*a,center+scale*b,color);
            }
        }
    };
    auto tuft = [&](glm::vec2 center, glm::vec2 scale, glm::vec4 color) {
        crown(center,scale,ink);
        crown(center,scale-glm::vec2(0.025f),color);
    };
    tuft({-0.39f,0.16f},{0.43f,0.43f},{0.20f,0.43f,0.26f,1});
    tuft({0.39f,0.17f},{0.43f,0.42f},{0.25f,0.52f,0.31f,1});
    tuft({0,0.40f},{0.49f,0.48f},{0.31f,0.60f,0.37f,1});
    tuft({-0.18f,0.15f},{0.29f,0.26f},{0.28f,0.54f,0.32f,1});
    m_geometry=scene.add(mesh);
}

void Broccoli::draw(const Scene& scene, const Renderer& renderer,
                    const Shader& shader, const glm::mat4& transform) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"model"),1,GL_FALSE,glm::value_ptr(transform));
    renderer.draw(scene[m_geometry]);
}
