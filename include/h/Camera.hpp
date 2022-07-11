#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <h/Ray.hpp>
class Camera{
    public:
        Camera(float ratio);
        void getCameraRay(float,float, Ray &);
    public:
        glm::vec3 m_viewPortHeight;
        glm::vec3 m_viewPortWidth;
        glm::vec3 m_focalLength;
        glm::vec3 m_origin;
        glm::vec3 m_bottomLeft;
};
#endif