#include <h/Camera.hpp>

Camera::Camera(float ratio){
    m_focalLength       = 1.0f;
    m_origin            = glm::vec3(0,0,0);
    m_viewPortHeight    = 1.0f;
    m_viewPortWidth     = ratio;
    m_xAxis             = glm::vec3(1.0,0,0);
    m_yAxis             = glm::vec3(0,1.0,0);
}
