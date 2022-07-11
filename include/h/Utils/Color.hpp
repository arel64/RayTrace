#ifndef COLOR
#define COLOR
#include <cstdint>
#include <algorithm>
//#include <glm/glm.hpp>
struct Color{
    float r;
    float g;
    float b;
    float alpha;

    
    Color(){};
    Color(float r,float g,float b,float a=1.0f):r(r),g(g),b(b),alpha(a){};
    Color operator+(const Color& rhs) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */
        
        auto r = std::clamp(this->r+rhs.r,0.0f,1.0f);
        auto g = std::clamp(this->g+rhs.g,0.0f,1.0f);
        auto b = std::clamp(this->b+rhs.b,0.0f,1.0f);
        return Color(r,g,b); // return the result by reference
    }
    Color& operator+=(const Color& rhs) 
    {               
        *this = *this + rhs;      
        return *this; 
    }
    Color& operator=(const Color& colorB){
        this->r = colorB.r;
        this->g = colorB.g;
        this->b = colorB.b;
        this->alpha = colorB.alpha;
        return *this;
    }
    friend Color operator-(const Color& color) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */

        return Color(std::clamp(-color.r,0.0f,1.0f),std::clamp(-color.g,0.0f,1.0f),std::clamp(-color.b,0.0f,1.0f)); // return the result by reference
    }
    friend Color operator*(const Color& color,float scalar) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */
        return Color(
            std::clamp(((color.r*scalar)),0.0f,1.0f),std::clamp(((color.g*scalar)),0.0f,1.0f),std::clamp(((color.b*scalar)),0.0f,1.0f)
        );

    }
    friend Color operator*(float scalar,const Color& color) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        return color*scalar;

    }
    
    friend Color operator*(const Color& colorA,const Color& colorB) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */
        return Color(
            colorA.r*colorB.r,
            colorA.g*colorB.g,
            colorA.b*colorB.b,
            colorA.alpha*colorB.alpha
        );

    }
    Color& operator*=(const Color& other) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */
        *this = (*this)*(other);
        return (*this);

    }
    friend Color operator/(const Color& color,float scalar) // compound assignment (does not need to be a member,
    {                           // but often is, to modify the private members)
        /* addition of rhs to *this takes place here */
        return color*(1/scalar); // return the result by reference
    }
    friend Color operator/(float scalar,const Color& color){
        return color*scalar;
    }
    inline sf::Color toSFMLColor(){
        return sf::Color(r*255,g*255,b*255,alpha*255);
    }
};
#endif