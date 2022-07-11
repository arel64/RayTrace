#ifndef MATERIAL
#define MATERIAL

#include <h/Ray.hpp>
#include <h/Hittable.hpp>
#include <h/Utils/RandomReal.hpp>

class Material{
    public:
        virtual void scatter(Ray&,float&,HitRecord&,RandomReal&) = 0;

};


#endif 
