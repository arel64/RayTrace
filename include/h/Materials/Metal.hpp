
#ifndef METAL
#define METAL

#include <h/Materials/Material.hpp>

class Metal : public Material{
    public:
        Metal(const Color& albedo): m_albedo(albedo){};
        virtual bool scatter(Ray&,Color&,HitRecord&,RandomReal&)override;
        const Color& getAlbedo(){return m_albedo;};
    private:
        Color m_albedo; 
};

#endif 
