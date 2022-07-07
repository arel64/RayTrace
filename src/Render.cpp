#include <h/Render.hpp>


void Render::startRender(sf::VertexArray* pixles){
    //Should interact with scene
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
            ((*pixles)[i*sceneHeight + j]).color =  rayColor(ray);

        }
    }

}

sf::Color Render::rayColor(const Ray &ray){

    if (hitSphere(glm::vec3(0,0,-1), 0.1, ray))
        return sf::Color(255, 0, 0);

    glm::vec3 rayNormDirection = glm::normalize(ray.getDirection());
    auto t = 0.5*(rayNormDirection.y + 1.0);
    return sf::Color(255*(1.0-t), 255*(1.0-t),255*1.0) + sf::Color(t*0.1*255,t*0.7*255,t* 1.0*255);
}
bool Render::hitSphere(const glm::vec3& sphereCenter, double radius, const Ray& ray) {
    glm::vec3 oc = ray.getOrigin() - sphereCenter;
    auto a = glm::dot(ray.getDirection(), ray.getDirection());
    auto b = 2.0 * dot(oc, ray.getDirection());
    auto c = dot(oc, oc) - radius*radius;
    
    auto discriminant = b*b - 4*a*c;

    if(discriminant > 0){
        return true;
    }
    return false;
}