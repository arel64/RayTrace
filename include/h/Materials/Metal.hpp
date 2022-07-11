
#ifndef METAL
#define METAL

#include <h/Materials/Material.hpp>

class Metal : public Material{
    public:
        Metal(float albedo): m_albedo(albedo){};
        virtual bool scatter(Ray&,float&,HitRecord&,RandomReal&)override;
        float getAlbedo(){return m_albedo;};
    private:
        float m_albedo; 
};

#endif 
