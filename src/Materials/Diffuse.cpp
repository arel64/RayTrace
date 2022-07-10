#include <h/Materials/Diffuse.hpp>


void Diffuse::scatter(Ray& ray,float& attenuation,HitRecord& rec,RandomReal& generator){
        
        glm::vec3 reflectedTargetPoint;
        generator.findRandPointOnUnitSphereRadius(reflectedTargetPoint);
        reflectedTargetPoint = rec.hitPoint + rec.normal + reflectedTargetPoint;


        ray.m_origin = rec.hitPoint;
        ray.m_direction = reflectedTargetPoint - rec.hitPoint;

        attenuation = m_albedo;

}