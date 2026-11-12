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
    // Nuvole composte da ellissi: prima l'intera ombra, poi i lobi chiari.
    // Restano dietro ad alberi ed edifici grazie all'ordine di disegno.
    auto cloud = [&](float x, float y, float size) {
        const glm::vec4 shadow(0.68f,0.83f,0.89f,1);
        const glm::vec4 white(0.95f,0.98f,0.98f,1);
        struct Lobe { float x,y,rx,ry; };
        const Lobe lobes[] = {
            {-0.26f,0,0.17f,0.065f}, {-0.12f,0.025f,0.14f,0.09f},
            {0,0.065f,0.15f,0.115f}, {0.15f,0.025f,0.13f,0.09f},
            {0.27f,-0.005f,0.15f,0.06f}
        };
        for (const auto& l : lobes)
            ellipse(x+l.x*size,y+(l.y-0.025f)*size,l.rx*size,l.ry*size,shadow);
        for (const auto& l : lobes)
            ellipse(x+l.x*size,y+(l.y+0.012f)*size,l.rx*size,l.ry*0.82f*size,white);
    };
    cloud(0.95f,0.88f,0.60f);
    cloud(2.65f,0.78f,0.85f);
    cloud(4.10f,0.84f,0.70f);
    cloud(5.70f,0.70f,1.0f);
    cloud(7.10f,0.87f,0.65f);
    cloud(8.65f,0.84f,0.75f);
    cloud(9.65f,0.73f,0.65f);

    rect(0,-1,10,0.90f,{0.33f,0.34f,0.40f,1}); // strada
    rect(0,-0.20f,10,0.12f,{0.69f,0.68f,0.70f,1}); // marciapiede
    rect(0,-0.09f,10,0.20f,{0.36f,0.62f,0.39f,1});
    for(float x=0;x<10;x+=0.45f) rect(x,-0.88f,0.24f,0.012f,{0.94f,0.85f,0.58f,1});
    for(float x=0.25f;x<10;x+=0.55f){
        rect(x,0.02f,0.035f,0.30f,{0.39f,0.29f,0.23f,1});
        ellipse(x,0.35f,0.17f,0.20f,{0.22f,0.44f,0.29f,1});
    }
    // Casa dei Simpson: volumi e particolari ispirati al riferimento frontale.
    const glm::vec4 peach(0.83f,0.63f,0.46f,1), roof(0.46f,0.28f,0.13f,1);
    const glm::vec4 trim(0.40f,0.26f,0.17f,1), pale(0.76f,0.74f,0.66f,1);
    auto quad=[&](glm::vec2 a,glm::vec2 b,glm::vec2 c,glm::vec2 d,glm::vec4 color){
        tri(a,b,c,color);tri(a,c,d,color);
    };
    // Semicerchio: pensiline e sommità della porta.
    auto arch=[&](float x,float y,float rx,float ry,glm::vec4 color){
        for(int i=0;i<32;++i){float a=3.14159265f*i/32,b=3.14159265f*(i+1)/32;
            tri({x,y},{x+rx*std::cos(a),y+ry*std::sin(a)},
                      {x+rx*std::cos(b),y+ry*std::sin(b)},color);}
    };
    // Vialetto e ingresso del garage, sul prato davanti alla casa.
    quad({0.79f,-0.085f},{1.14f,-0.085f},{1.05f,0.06f},{0.88f,0.06f},pale);
    quad({1.57f,-0.085f},{2.32f,-0.085f},{2.17f,0.08f},{1.68f,0.08f},pale);
    framed(0.30f,0.025f,1.30f,0.63f,peach);
    rect(0.315f,0.03f,0.028f,0.60f,{0.74f,0.52f,0.37f,1});
    // Camino dietro il tetto.
    framed(0.43f,0.75f,0.10f,0.16f,peach);
    framed(0.415f,0.88f,0.13f,0.035f,trim);
    // Falda trapezoidale piena, senza gli angoli vuoti della prima bozza.
    quad({0.21f,0.65f},{1.69f,0.65f},{1.47f,0.88f},{0.43f,0.88f},ink);
    quad({0.235f,0.665f},{1.665f,0.665f},{1.46f,0.866f},{0.44f,0.866f},roof);
    // Tegole suggerite da piccoli tratti sfalsati, tutti dentro la falda.
    for(int row=0;row<4;++row)for(int col=0;col<9;++col){
        float x=0.45f+col*0.11f+(row%2)*0.035f;
        float y=0.69f+row*0.043f;
        rect(x,y,0.045f+(col%3)*0.008f,0.004f,trim);
    }
    rect(0.22f,0.63f,1.46f,0.025f,ink);
    rect(0.23f,0.635f,1.44f,0.013f,pale);
    // Antenna sottile.
    rect(0.66f,0.83f,0.006f,0.15f,ink);
    rect(0.60f,0.94f,0.13f,0.006f,ink);
    rect(0.625f,0.90f,0.08f,0.006f,ink);
    // Due finestre del piano superiore con tende e riflessi.
    for(float x:{0.43f,1.15f}){
        framed(x,0.445f,0.30f,0.17f,glass);
        rect(x+0.14f,0.448f,0.012f,0.165f,trim);
        rect(x+0.016f,0.455f,0.018f,0.145f,{0.33f,0.57f,0.57f,1});
        rect(x+0.267f,0.455f,0.016f,0.145f,{0.33f,0.57f,0.57f,1});
        quad({x+0.06f,0.57f},{x+0.065f,0.58f},{x+0.11f,0.52f},{x+0.105f,0.51f},{0.76f,0.89f,0.83f,1});
        rect(x-0.008f,0.435f,0.316f,0.013f,trim);
    }
    // Porta arcuata con cornice, maniglia e battente.
    rect(0.83f,0.035f,0.25f,0.215f,ink);arch(0.955f,0.25f,0.125f,0.105f,ink);
    rect(0.844f,0.04f,0.222f,0.21f,trim);arch(0.955f,0.25f,0.111f,0.091f,trim);
    glm::vec4 door(0.76f,0.39f,0.28f,1);
    rect(0.859f,0.045f,0.192f,0.205f,door);arch(0.955f,0.25f,0.096f,0.077f,door);
    ellipse(0.883f,0.145f,0.009f,0.014f,ink);
    ellipse(0.958f,0.266f,0.012f,0.016f,pale);
    ellipse(0.958f,0.244f,0.009f,0.009f,ink);
    rect(0.82f,0.024f,0.27f,0.017f,ink);rect(0.81f,0.009f,0.29f,0.014f,pale);
    // Finestre del piano terra e pensiline a cupola marroni.
    for(float x:{0.42f,1.17f}){
        framed(x,0.075f,0.28f,0.22f,glass);
        for(float offset:{0.045f,0.135f,0.23f})rect(x+offset,0.08f,0.008f,0.21f,trim);
        rect(x,0.18f,0.28f,0.009f,trim);
        arch(x+0.14f,0.295f,0.155f,0.075f,ink);
        arch(x+0.14f,0.297f,0.142f,0.061f,roof);
        rect(x+0.135f,0.297f,0.008f,0.061f,trim);
        rect(x-0.01f,0.067f,0.30f,0.013f,trim);
    }
    // Garage: frontone, finestrina e pannelli orizzontali.
    framed(1.60f,0.025f,0.65f,0.36f,peach);
    tri({1.58f,0.375f},{2.27f,0.375f},{1.925f,0.57f},ink);
    tri({1.61f,0.38f},{2.24f,0.38f},{1.925f,0.55f},peach);
    quad({1.55f,0.38f},{1.57f,0.365f},{1.925f,0.555f},{1.925f,0.58f},trim);
    quad({1.925f,0.555f},{2.28f,0.365f},{2.30f,0.38f},{1.925f,0.58f},trim);
    framed(1.865f,0.41f,0.12f,0.09f,glass);
    rect(1.921f,0.415f,0.008f,0.08f,trim);rect(1.87f,0.45f,0.11f,0.008f,trim);
    framed(1.66f,0.025f,0.53f,0.31f,trim);
    rect(1.68f,0.04f,0.49f,0.275f,{0.69f,0.48f,0.31f,1});
    for(int i=1;i<5;++i)rect(1.68f,0.04f+i*0.055f,0.49f,0.006f,trim);
    // Siepi a ciuffi davanti alla facciata.
    for(float x:{0.36f,0.72f,1.15f,1.51f}){
        for(int i=0;i<3;++i){
            float cx=x+(i-1)*0.045f,cy=0.045f+(i==1?0.035f:0);
            ellipse(cx,cy,0.055f,0.065f,ink);
            ellipse(cx,cy+0.004f,0.049f,0.059f,{0.35f,0.53f,0.24f,1});
        }
    }
    // Giunti del marciapiede e cassetta postale.
    for(float x=0.1f;x<2.6f;x+=0.30f)rect(x,-0.19f,0.005f,0.10f,{0.45f,0.46f,0.47f,1});
    rect(1.43f,-0.07f,0.013f,0.14f,trim);
    framed(1.39f,0.045f,0.105f,0.065f,{0.28f,0.39f,0.46f,1});
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
