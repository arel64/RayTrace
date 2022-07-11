#include <h/Materials/Metal.hpp>
bool Metal::scatter(Ray& ray,Color& attenuation,HitRecord& rec,RandomReal& generator){

        //Reflection formula: v - 2*dot(v,n)*n

        glm::vec3 reflectedTarget;
        reflectedTarget = ray.m_direction -2*glm::dot(ray.m_direction,rec.normal)*rec.normal;


        if(glm::dot(rec.normal,reflectedTarget) < 0){
            //reflected into sphere, abort
            return false;
        }
        ray.m_origin = rec.hitPoint;
        ray.m_direction = reflectedTarget;

        attenuation = m_albedo;
        return true;
        

} 
