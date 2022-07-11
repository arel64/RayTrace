#ifndef RAY
#define RAY
#include "SFML/Graphics/Color.hpp"
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <stdint.h>
#include <h/Utils/Color.hpp>
struct Ray{
    
    public:
        //Ray() {}
        Ray(uint16_t reflectionsLeft,Color color = Color(1,1,1)):
            m_reflectionsLeft(reflectionsLeft),m_color(color){};
        Ray(const glm::vec3& dire,const glm::vec3& orig,uint16_t reflectionsLeft,Color color = Color(1,1,1)):
            m_direction(dire),m_origin(orig),m_reflectionsLeft(reflectionsLeft),m_color(color){};
        
        glm::vec3   at(float t)const;

        glm::vec3   m_direction;
        glm::vec3   m_origin;
        uint16_t    m_reflectionsLeft;
        Color       m_color;
        
    
};
#endif