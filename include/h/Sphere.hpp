#ifndef SPHERE
#define SPEHERE
#include <h/Hittable.hpp>

class Sphere : public Hittable{
    public:
        Sphere(glm::vec3 cen,float rad): m_center(cen),m_radius(rad){};
        virtual bool hit(const Ray& ray,float tMin,float tMax,HitRecord& rec) const override;
    private:
        glm::vec3 m_center;
        float m_radius;

};
#endif