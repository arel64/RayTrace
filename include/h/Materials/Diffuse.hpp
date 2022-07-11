#ifndef DIFFUSE
#define DIFFUSE

#include <h/Materials/Material.hpp>
class Diffuse : public Material{
    public:
        Diffuse(float albedo): m_albedo(albedo){};
        virtual void scatter(Ray&,float&,HitRecord&,RandomReal&)override;
        float getAlbedo(){return m_albedo;};
    private:
        float m_albedo; 
};

#endif 
