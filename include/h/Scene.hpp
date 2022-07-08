#ifndef SCENE
#define SCENE
#include <h/Camera.hpp>
#include <h/Hittable.hpp>
#include <memory>


class Scene{
    public:
        Scene(uint16_t width,uint16_t height,uint16_t antiAliasingSample) :
                 m_width(width),m_height(height),m_antiAliasingSample(antiAliasingSample){};
        float getRatio()const{return ((float)m_width)/m_height;};
        uint16_t getWidth()const{return m_width;};
        uint16_t getHeight()const{return m_height;};
        uint16_t getAntiAliasingSample()const{return m_antiAliasingSample;};
        uint32_t getSize()const{return m_height*m_width;};
        
        void addObject(std::shared_ptr<Hittable> object);
        bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const;
    private:
        std::vector<std::shared_ptr<Hittable>> m_objects;
        const uint16_t m_antiAliasingSample; //1 Means no AntiAliasing
        const uint16_t m_width;
        const uint16_t m_height;
        
};
#endif
