#ifndef HITRECORD
#define HITRECORD

#include <h/Ray.hpp>
#include <memory>
class Material;


struct HitRecord{
    std::shared_ptr<Material> material;
    glm::vec3 hitPoint;
    glm::vec3 normal;
    float t;
    bool frontFaceNormal;

    inline void setFaceNormal(const Ray& ray,const glm::vec3& outwardNormal){
        frontFaceNormal = glm::dot(ray.m_direction,outwardNormal) < 0;
        normal = frontFaceNormal ? outwardNormal:-outwardNormal;
    }
    
}typedef HitRecord;

class Hittable{
    public:
        virtual bool hit(const Ray& ray,float tMin,float tMax,HitRecord& rec) const = 0;
};


#endif