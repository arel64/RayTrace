#ifndef MATERIAL
#define MATERIAL

#include <h/Ray.hpp>
#include <h/Hittable.hpp>
#include <h/Utils/RandomReal.hpp>
#include <h/Utils/Color.hpp>

class Material{
    public:
        virtual bool scatter(Ray&,Color&,HitRecord&,RandomReal&) = 0;

};


#endif 
