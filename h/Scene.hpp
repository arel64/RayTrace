#ifndef SCENE
#define SCENE
#include <h/Camera.hpp>
#include <h/Hittable.hpp>
#include <memory>


class Scene{
    public:
        Scene(float ratio,Camera& camera) :
                 m_ratio(ratio),m_camera(camera){};
        float           getRatio()const{return m_ratio;};

        const Camera&   getCamera()const{return m_camera;};


        void addObject(std::shared_ptr<Hittable> object);
        bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const;
    private:
        std::vector<std::shared_ptr<Hittable>> m_objects;
        float m_ratio;
        Camera& m_camera;
        
};
#endif
