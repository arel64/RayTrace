#include <h/Camera.hpp>

Camera::Camera(float ratio)
{
    m_focalLength       = glm::vec3(0,0,1.0);
    m_origin            = glm::vec3(0,0,0);

    //TODO:: THIS SHOULD SCALE
    m_viewPortHeight    = glm::vec3(0,-2.0,0);
    m_viewPortWidth     = glm::vec3(2.0,0,0)*ratio;

    m_bottomLeft        =m_origin - m_viewPortWidth*(0.5f) - m_viewPortHeight*(0.5f) - m_focalLength;
   
}
void Camera::getCameraRay(float xCoef,float yCoef, Ray &ray)
{
    ray.m_direction = m_bottomLeft + m_viewPortWidth*xCoef + m_viewPortHeight*yCoef - m_origin;
    ray.m_origin = m_origin;
}
