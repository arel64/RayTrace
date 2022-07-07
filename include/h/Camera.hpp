#include <glm/glm.hpp>
class Camera{
    public:
        Camera(float ratio );

    public:
        glm::vec3 m_viewPortHeight;
        glm::vec3 m_viewPortWidth;
        glm::vec3 m_focalLength;
        glm::vec3 m_origin;
};