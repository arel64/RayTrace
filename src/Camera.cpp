
#include <h/Camera.hpp>

Camera::Camera(float ratio){
    m_focalLength       = glm::vec3(0,0,1.0);
    m_origin            = glm::vec3(0,0,0);
    m_viewPortHeight    = glm::vec3(0,1.0,0);
    m_viewPortWidth     = glm::vec3(1.0,0,0)*ratio;
}
