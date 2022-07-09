
#include <h/Sphere.hpp>
bool Sphere::hit(const Ray& ray,float tMin,float tMax,HitRecord& rec) const{

    glm::vec3 rayDirection = ray.m_direction;
    glm::vec3 oc = ray.m_origin - m_center;
    //Quadratic formula with factor of 2 removed from it
    float a = glm::dot(rayDirection, rayDirection);
    float b = dot(oc, rayDirection);
    float c = dot(oc, oc) - m_radius*m_radius;
    
    float discriminant = b*b - a*c;

    if(discriminant < 0){
        return false;
    }
     
    
    // Find the nearest root that lies in the acceptable range.
    float sqrd = glm::sqrt(discriminant);
    float root = (-b - sqrd) / a;
    
    if (root < tMin || tMax < root) {
        root = (-b + sqrd) / a;
        if (root < tMin || tMax < root)
            return false;
    }

    //Update hit record
    rec.t = root;
    rec.hitPoint = ray.at(rec.t);
    glm::vec3 outwardNormal = (rec.hitPoint - m_center) / m_radius;
    rec.setFaceNormal(ray, outwardNormal);


    return true;
}
