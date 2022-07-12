#ifndef COLOR
#define COLOR

#include <cstdint>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <stdint.h>

struct Color{

    float r;
    float g;
    float b;
    float alpha;

    
    Color(){};
    Color(float r,float g,float b,float a=1.0f):r(r),g(g),b(b),alpha(a){};

    Color   operator+   (const Color&);
    Color&  operator+=  (const Color&);

    Color&  operator=   (const Color&);
    Color&  operator*=  (const Color&);
  


    friend Color operator*(const Color&,const Color&);
    friend Color operator*(const Color&,float);
    friend Color operator*(float,const Color&);
    
    
    friend Color operator/(const Color& ,float);
    friend Color operator/(float ,const Color&);

    inline sf::Color toSFMLColor(){return sf::Color(r*255,g*255,b*255,alpha*255);};
    /*inline void gammaCorrect(uint16_t antiAliasingSample){
        double scale = 1.0 / antiAliasingSample;
        this->r = glm::sqrt(scale * r);
        this->g = glm::sqrt(scale * g);
        this->b = glm::sqrt(scale * b);
    };*/
};
#endif