
#ifndef METAL
#define METAL

#include <h/Materials/Material.hpp>

class Metal : public Material{
    public:
        Metal(const Color& albedo,float fuzz): m_albedo(albedo),m_fuzz(fuzz){};
        const Color& getAlbedo() const  {return m_albedo;};

        virtual bool scatter(Ray&,HitRecord&,RandomReal&) override;

    private:
        const Color m_albedo;
        const float m_fuzz;
};

#endif 
