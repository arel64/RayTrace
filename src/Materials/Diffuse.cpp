#include <h/Materials/Diffuse.hpp>


bool Diffuse::scatter(Ray& ray,HitRecord& rec,RandomReal& generator){

        glm::vec3 scatteredTarget;
        generator.findRandPointOnUnitSphereRadius(scatteredTarget);

        scatteredTarget = rec.normal + scatteredTarget;

        if(scatteredTarget.length()<=0.0001f){
                //Vectors are opposite, prevent 0 direction
                scatteredTarget = rec.normal;
        }

        ray.m_origin    = rec.hitPoint;
        ray.m_direction = scatteredTarget;
        ray.m_color    *= m_albedo;

        return true;

} 
