#ifndef DIFFUSE
#define DIFFUSE

#include <h/Materials/Material.hpp>
class Diffuse : public Material{
    public:
        Diffuse(const Color& albedo): m_albedo(albedo){};
        virtual bool scatter(Ray&,Color&,HitRecord&,RandomReal&)override;
        const Color& getAlbedo(){return m_albedo;};
    private:
        Color m_albedo; 
};

#endif 
