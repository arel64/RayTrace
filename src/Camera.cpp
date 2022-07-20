#include <glm/geometric.hpp>
#include <h/Camera.hpp>

Camera::Camera(const float& ratio,const float& fovAngleDeg,
                    const glm::vec3 &lookFrom ,
                    const glm::vec3 &lookAt   ,
                    const glm::vec3 &vUp)
{

    float fovAngleRad       = glm::radians(fovAngleDeg);
    float verticalScaleFov  = glm::tan(fovAngleRad/2);
    float viewPortHeight    = 2.0f * verticalScaleFov;
    float viewPortWidth     = viewPortHeight * ratio;
    
    m_viewPortRatio         = ratio;
    m_fovRad                = fovAngleRad;
    m_origin                = lookFrom;

    glm::vec3 focalPointVec = glm::normalize(lookFrom-lookAt);
    glm::vec3 viewPortWidthVecUnscaled = glm::normalize(glm::cross(vUp,focalPointVec));
    glm::vec3 viewPortHeightVecUnscaled = glm::cross(focalPointVec,viewPortWidthVecUnscaled);

    m_viewPortHeightVec = viewPortHeightVecUnscaled * viewPortHeight;
    m_viewPortWidthVec  = viewPortWidthVecUnscaled  * viewPortWidth;

    m_bottomLeft       = m_origin - m_viewPortWidthVec*(0.5f) - m_viewPortHeightVec*(0.5f) - focalPointVec;
   
}
void Camera::getCameraRay(float xCoef,float yCoef, Ray &outRay) const
{
    outRay.m_direction = m_bottomLeft + m_viewPortWidthVec * xCoef + m_viewPortHeightVec * yCoef - m_origin;
    outRay.m_origin = m_origin;
}
