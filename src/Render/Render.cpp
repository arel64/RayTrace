
#include <h/Render/Render.hpp>

inline double getRealRand();
void Render::startRender(sf::VertexArray* pixles,const Scene& scene){

    auto startTime = std::chrono::steady_clock::now();
    
    std::clog <<  "Render start" << std::endl;
    
    uint16_t sceneHeight = m_scene.getHeight();
    uint16_t sceneWidth = m_scene.getWidth();
    
    Camera c(m_scene.getRatio());

    //uint64_t duration = 0;

    for (int j = sceneHeight -1; j >= 0; --j) {
        for (int i = 0; i < sceneWidth -1; ++i) {

            uint32_t accumulateR,accumulateG,accumulateB;
            accumulateR=accumulateG=accumulateB=0;

            uint16_t antiAliasingSample =scene.getAntiAliasingSample();
            assert(antiAliasingSample>0);


        
            //This is for each pixel, tread lightly!
           
            sf::Color temp;
            for(int m = 0 ; m < antiAliasingSample; m++){
                //auto starta = std::chrono::steady_clock::now();
                float xCoef = (float)(i+ getRealRand())/sceneWidth; 
                float yCoef = (float)(j+ getRealRand())/sceneHeight; 
                //auto enda = std::chrono::steady_clock::now();

                //duration +=(enda - starta).count();
                Ray currentPixelRay = c.getCameraRay(xCoef,yCoef);
                rayColor(scene,currentPixelRay,temp);
                
                
                accumulateR += temp.r;
                accumulateG += temp.g;
                accumulateB += temp.b;
            }
            sf::Color pixelColor(
                accumulateR/antiAliasingSample,
                accumulateG/antiAliasingSample,
                accumulateB/antiAliasingSample
            );

            ((*pixles)[i*sceneHeight + j]).position = sf::Vector2f(i,j);
            ((*pixles)[i*sceneHeight + j]).color =  pixelColor;

        }
    }
    auto endTime = std::chrono::steady_clock::now();
    //std::clog <<  "[Render] Real Number: " << duration/(1000*1000) << " ms" ;
    std::clog <<  "[Render] Total: " << (endTime-startTime).count()/(1000*1000) << " ms" ;
}
//TODO:: This whole function is temporary
void Render::rayColor(const Scene& scene,const Ray &ray,sf::Color& outColor){
    HitRecord rec;

    if(scene.hit(ray,0.0f,std::numeric_limits<double>::infinity(),rec)){
        glm::vec3 rayNormalAt = glm::normalize(ray.at(rec.t) - glm::vec3(0,0,-1));
        
        outColor.r =255;
        outColor.g =glm::abs(rayNormalAt.z)*255;
        outColor.b =255;
        return;
    }
    

    glm::vec3 rayNormDirection = glm::normalize(ray.getDirection());
    float t = 0.5*(rayNormDirection.y + 1.0);

    outColor.r =255*(1.0-t) + t*0.1*255;
    outColor.g =255*(1.0-t) + t*0.7*255;
    outColor.b =255*(1.0-t) + t* 1.0*255;

    //return sf::Color(255*(1.0-t), 255*(1.0-t),255*(1.0-t)) + sf::Color(t*0.1*255,t*0.7*255,t* 1.0*255);
}
//Generate Random number from 0-1
inline double getRealRand(){
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_real_distribution<double> rand(0.0,1.0);
    return rand(rng);
}