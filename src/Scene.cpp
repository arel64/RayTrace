
#include <h/Scene.hpp>

bool Scene::hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const{
    HitRecord tempRec;
    float closestHit = tMax;
    bool isHit = false;
    for(const auto& object :m_objects){
        if(object->hit(ray,tMin,closestHit,tempRec)){
            closestHit = tempRec.t;
            isHit =true;
        }
    }
    rec = tempRec;
    return isHit;
}
void Scene::addObject(std::shared_ptr<Hittable> object){
    m_objects.emplace_back(object);
}
