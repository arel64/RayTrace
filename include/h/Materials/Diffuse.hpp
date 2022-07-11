#ifndef DIFFUSE
#define DIFFUSE

#include <h/Materials/Material.hpp>

/**
 * @brief Diffuse Material, scatters rays and changed thier color. 
 * 
 */
class Diffuse : public Material{
    public:
        Diffuse(const Color& albedo): m_albedo(albedo){};
        const Color& getAlbedo() const  {return m_albedo;};

        virtual bool scatter(Ray&,HitRecord&,RandomReal&) override;

    private:
        const Color m_albedo; 
};

#endif 
