#include "h/Ray.hpp"
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>
#include <h/Materials/Dielectric.hpp>


bool Dielectric::scatter(Ray& ray,HitRecord& rec,RandomReal& generator){
    // refractRay , math from snells law.
    glm::vec3 unitVectorRefractedRay = glm::normalize(ray.m_direction);

    float cosAngle = glm::min(glm::dot(-unitVectorRefractedRay, rec.normal), 1.0f);
    //Flip material coeffiecent if needed
    float refractionCoeficent = rec.frontFaceNormal ? (1.0f/m_refractionIndex):m_refractionIndex; 

    glm::vec3 perpendicularRayDirection =  refractionCoeficent*(unitVectorRefractedRay + cosAngle*rec.normal);
    
    glm::vec3 paralelRayDirection =
        rec.normal*
            ((float)(-glm::sqrt(glm::abs(1.0 - glm::pow(perpendicularRayDirection.length(),2)))));
    
    ray.m_direction = perpendicularRayDirection + paralelRayDirection;
    ray.m_origin = rec.hitPoint;
       
    return true;

}

