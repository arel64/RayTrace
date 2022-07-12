#ifndef MATERIAL
#define MATERIAL

#include <h/Ray.hpp>
#include <h/Hittable.hpp>
#include <h/Utils/RandomReal.hpp>
#include <h/Utils/Color.hpp>

/**
 * @brief Abstract Material
 * 
 */
class Material{
    public:
        virtual bool scatter(Ray&,HitRecord&,RandomReal&) = 0;

};


#endif 
