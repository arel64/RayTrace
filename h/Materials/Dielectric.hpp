#ifndef DIELECTRIC
#define DIELECTRIC

#include <h/Materials/Material.hpp>

/**
 * @brief Diffuse Material, scatters rays and changed thier color. 
 * 
 */
class Dielectric : public Material{
    public:
        Dielectric(float refractionIndex): m_refractionIndex(refractionIndex){};
        const float     getRefractionIndex() const  {return m_refractionIndex;};
        virtual bool    scatter(Ray&,HitRecord&,RandomReal&) override;

    private:
        const float m_refractionIndex; 
};

#endif 
