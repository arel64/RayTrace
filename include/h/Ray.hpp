#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

class Ray{
    
    public:
        Ray(const glm::vec3& dire,const glm::vec3& orig): m_direction(dire),m_origin(orig){};
        sf::Color   rayColor    (Ray &ray)       ;
        glm::vec3   at          (float t)   const;
        glm::vec3   getDirection()          const{ return m_direction;};
        glm::vec3   getOrigin   ()          const{ return m_origin;};
    private:
        glm::vec3 m_direction;
        glm::vec3 m_origin;
    
};
