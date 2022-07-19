#include <h/Camera.hpp>

Camera::Camera(const float& ratio,const float& fovAngleDeg)
{
    float fovAngleRad       = glm::radians(fovAngleDeg);
    float verticalScaleFov  = glm::tan(fovAngleRad/2);
    float viewPortHeight    = 2.0f * verticalScaleFov;
    float viewPortWidth     = viewPortHeight * ratio;
    
    m_viewPortRatio         = ratio;
    m_fovRad                = fovAngleDeg;

    m_focalLengthVec           = glm::vec3(0,0,1.0);
    m_origin                = glm::vec3(0,0,0);

    m_viewPortWidthVec      = glm::vec3(viewPortWidth,0,0);
    m_viewPortHeightVec     = glm::vec3(0,viewPortHeight,0);

    m_bottomLeft            = m_origin - m_viewPortWidthVec*(0.5f) - m_viewPortHeightVec*(0.5f) - m_focalLengthVec;
   
}
void Camera::getCameraRay(float xCoef,float yCoef, Ray &ray) const
{
    ray.m_direction = m_bottomLeft + m_viewPortWidthVec * xCoef + m_viewPortHeightVec * yCoef - m_origin;
    ray.m_origin = m_origin;
}
