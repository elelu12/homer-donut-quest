#include "Landscape.h"
#include "Scene.h"
#include "Renderer.h"
#include "Shader.h"
#include "MeshData.h"
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
void Landscape::create(Scene& scene)
{
    MeshData m;
    const glm::vec4 ink(0.20f,0.16f,0.21f,1), glass(0.55f,0.78f,0.75f,1);
    auto tri=[&](glm::vec2 a,glm::vec2 b,glm::vec2 c,glm::vec4 color){
        for(auto p:{a,b,c}){m.positions.emplace_back(p,0);m.colors.push_back(color);}
    };
    auto rect=[&](float x,float y,float w,float h,glm::vec4 c){
        tri({x,y},{x+w,y},{x+w,y+h},c);tri({x,y},{x+w,y+h},{x,y+h},c);
    };
    auto framed=[&](float x,float y,float w,float h,glm::vec4 c){
        rect(x,y,w,h,ink);rect(x+0.012f,y+0.012f,w-0.024f,h-0.024f,c);
    };
    auto ellipse=[&](float x,float y,float rx,float ry,glm::vec4 c){
        for(int i=0;i<40;++i){float a=i*6.283185f/40,b=(i+1)*6.283185f/40;
        tri({x,y},{x+rx*std::cos(a),y+ry*std::sin(a)},{x+rx*std::cos(b),y+ry*std::sin(b)},c);}
    };
    rect(0,-1,10,0.90f,{0.33f,0.34f,0.40f,1}); // strada
    rect(0,-0.20f,10,0.12f,{0.69f,0.68f,0.70f,1}); // marciapiede
    rect(0,-0.09f,10,0.20f,{0.36f,0.62f,0.39f,1});
    for(float x=0;x<10;x+=0.45f) rect(x,-0.88f,0.24f,0.012f,{0.94f,0.85f,0.58f,1});
    for(float x=0.25f;x<10;x+=0.55f){
        rect(x,0.02f,0.035f,0.30f,{0.39f,0.29f,0.23f,1});
        ellipse(x,0.35f,0.17f,0.20f,{0.22f,0.44f,0.29f,1});
    }
    // Casa dei Simpson: facciata pesca, tetto bruno e garage laterale.
    framed(0.35f,0.02f,1.24f,0.62f,{0.88f,0.62f,0.47f,1});
    tri({0.25f,0.64f},{1.70f,0.64f},{1.48f,0.89f},ink);
    tri({0.25f,0.64f},{1.48f,0.89f},{0.49f,0.89f},ink);
    rect(0.42f,0.66f,1.08f,0.19f,{0.43f,0.28f,0.18f,1});
    framed(0.85f,0.02f,0.22f,0.30f,{0.66f,0.34f,0.31f,1});
    for(float x:{0.47f,1.17f}) for(float y:{0.10f,0.43f}) {
        framed(x,y,0.26f,0.16f,glass);rect(x+0.12f,y,0.012f,0.16f,ink);
    }
    framed(1.60f,0.02f,0.55f,0.36f,{0.84f,0.57f,0.43f,1});
    tri({1.55f,0.38f},{2.20f,0.38f},{1.87f,0.58f},{0.43f,0.28f,0.18f,1});
    framed(1.67f,0.02f,0.40f,0.27f,{0.74f,0.50f,0.39f,1});
    // Moe's: finestrini a rombi, porta e travi viola.
    framed(7.4f,0.02f,1.80f,0.69f,{0.88f,0.61f,0.49f,1});
    rect(7.38f,0.67f,1.84f,0.035f,{0.40f,0.22f,0.43f,1});
    framed(8.12f,0.02f,0.33f,0.37f,{0.49f,0.19f,0.21f,1});
    ellipse(8.28f,0.27f,0.055f,0.055f,ink);
    ellipse(8.28f,0.27f,0.042f,0.042f,{0.78f,0.70f,0.47f,1});
    for(float x:{7.55f,8.63f}) {
        framed(x,0.19f,0.40f,0.23f,{0.37f,0.20f,0.43f,1});
        for(int i=0;i<5;++i)for(int j=0;j<3;++j){
            float cx=x+0.045f+i*0.077f,cy=0.232f+j*0.065f;
            glm::vec4 c=(i+j)%2?glm::vec4(0.95f,0.56f,0.16f,1):glm::vec4(0.22f,0.58f,0.26f,1);
            tri({cx-0.034f,cy},{cx,cy+0.030f},{cx+0.034f,cy},c);
            tri({cx-0.034f,cy},{cx+0.034f,cy},{cx,cy-0.030f},c);
        }
    }
    framed(7.93f,0.46f,0.72f,0.18f,{0.78f,0.68f,0.83f,1});
    // Insegna MOE, lettere composte da rettangoli e triangoli.
    glm::vec4 red(0.68f,0.16f,0.20f,1);
    rect(7.99f,0.49f,0.02f,0.12f,red);rect(8.11f,0.49f,0.02f,0.12f,red);
    tri({8.0f,0.61f},{8.06f,0.53f},{8.06f,0.57f},red);
    tri({8.12f,0.61f},{8.06f,0.53f},{8.06f,0.57f},red);
    framed(8.18f,0.49f,0.10f,0.12f,red);
    rect(8.205f,0.515f,0.05f,0.07f,{0.78f,0.68f,0.83f,1});
    rect(8.34f,0.49f,0.02f,0.12f,red);
    for(float y:{0.49f,0.54f,0.59f})rect(8.34f,y,0.10f,0.02f,red);
    m_geometry=scene.add(m);
}
void Landscape::draw(const Scene& scene,const Renderer& renderer,const Shader& shader) const
{
    glm::mat4 identity(1);
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"model"),1,GL_FALSE,glm::value_ptr(identity));
    renderer.draw(scene[m_geometry]);
}
