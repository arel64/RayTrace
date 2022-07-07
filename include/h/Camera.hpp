#include <glm/glm.hpp>
class Camera{
    public:
        Camera(float ratio );

    public:
        float m_viewPortHeight;
        float m_viewPortWidth;
        float m_focalLength;
        glm::vec3 m_origin;
        glm::vec3 m_xAxis; 
        glm::vec3 m_yAxis; 
};