#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <h/Ray.hpp>
class Camera{
    public:
        Camera(const float& ratio,const float& fov,
                    const glm::vec3& lookFrom = glm::vec3(0,0,0),
                    const glm::vec3& lookAt   = glm::vec3(0,0,-1),
                    const glm::vec3& vUp      = glm::vec3(0,1,0) 
            );
        Camera(Camera& c):Camera(c.m_viewPortRatio,c.m_fovRad){};
        void getCameraRay(float,float, Ray &) const;
    public:
        float m_viewPortRatio;
        float m_fovRad;
        glm::vec3 m_viewPortHeightVec;
        glm::vec3 m_viewPortWidthVec;
        glm::vec3 m_origin;
        glm::vec3 m_bottomLeft;
};
#endif