
#include <h/Ray.hpp>

glm::vec3 Ray::at(float t) const{
    return m_origin + m_direction*t;
}
