#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <h/Ray.hpp>
class Camera{
    public:
        Camera(const float& ratio,const float& fov);
        Camera(Camera& c):Camera(c.m_viewPortRatio,c.m_fovRad){};
        void getCameraRay(float,float, Ray &) const;
    public:
        float m_viewPortRatio;
        float m_fovRad;
        glm::vec3 m_viewPortHeightVec;
        glm::vec3 m_viewPortWidthVec;
        glm::vec3 m_focalLengthVec;
        glm::vec3 m_origin;
        glm::vec3 m_bottomLeft;
};
#endif