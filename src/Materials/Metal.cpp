#include <glm/fwd.hpp>
#include <h/Materials/Metal.hpp>
bool Metal::scatter(Ray& ray,HitRecord& rec,RandomReal& generator){

        //Reflection formula: v - 2*dot(v,n)*n
        glm::vec3 fuzzVec;
        glm::vec3 reflectedTarget =
            ray.m_direction -2*glm::dot(ray.m_direction,rec.normal)*rec.normal;
        
        generator.findRandPointOnUnitSphereRadius(fuzzVec);
        

        if(glm::dot(rec.normal,reflectedTarget) < 0){
            //reflected into sphere, abort
            return false;
        }
        ray.m_origin        = rec.hitPoint;
        ray.m_direction     = reflectedTarget + fuzzVec*m_fuzz;
        ray.m_color         *= m_albedo;

        return true;
        

} 
