
#include <h/Render.hpp>

void Render::startRender(sf::VertexArray* pixles,const Scene& scene){

    auto startTime = std::chrono::steady_clock::now();
    std::clog <<  "Render start" << std::endl;
    
    uint16_t sceneHeight = m_scene.getHeight();
    uint16_t sceneWidth = m_scene.getWidth();
    
    Camera c(m_scene.getRatio());

    const glm::vec3 bottomLeft(
        c.m_origin -
        c.m_viewPortWidth*(0.5f) -
        c.m_viewPortHeight*(0.5f) -
        c.m_focalLength
    );

    for (int j = sceneHeight -1; j >= 0; --j) {
        for (int i = 0; i < sceneWidth -1; ++i) {

            float px = (float)i/sceneWidth; 
            float py = (float)j/sceneHeight; 

            Ray ray(bottomLeft + c.m_viewPortWidth*px + c.m_viewPortHeight*py,c.m_origin);

            ((*pixles)[i*sceneHeight + j]).position = sf::Vector2f(i,j);
            ((*pixles)[i*sceneHeight + j]).color =  rayColor(scene,ray);

        }
    }
    auto endTime = std::chrono::steady_clock::now();
    std::clog <<  "Render end: " << (endTime-startTime).count()/(1000*1000) << " ms" ;
}
//TODO:: This whole function is temporary
sf::Color Render::rayColor(const Scene& scene,const Ray &ray){
    HitRecord rec;

    if(scene.hit(ray,0.0f,std::numeric_limits<double>::infinity(),rec)){
        glm::vec3 rayNormalAt = glm::normalize(ray.at(rec.t) - glm::vec3(0,0,-1));
        return sf::Color(
            255,
            glm::abs(rayNormalAt.z)*255,
            255
        );   
    
    }
    

    glm::vec3 rayNormDirection = glm::normalize(ray.getDirection());
    float t = 0.5*(rayNormDirection.y + 1.0);

    return sf::Color(255*(1.0-t), 255*(1.0-t),255*(1.0-t)) + sf::Color(t*0.1*255,t*0.7*255,t* 1.0*255);
}
