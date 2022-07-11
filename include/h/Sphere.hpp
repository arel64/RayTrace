#ifndef SPHERE
#define SPHERE
#include <h/Hittable.hpp>
#include <memory>

class Sphere : public Hittable{
    public:
        Sphere(glm::vec3 cen,float rad,Material* material): m_center(cen),m_radius(rad),m_material(material){};
        float getRadius()const{ return m_radius;};
        const glm::vec3& getCenter()const { return m_center;};

        virtual bool hit(const Ray& ray,float tMin,float tMax,HitRecord& rec) const override;

    private:
        Material* m_material;
        glm::vec3 m_center;
        float m_radius;

};
#endif