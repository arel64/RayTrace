#include <h/Utils/Color.hpp>
    Color::Color(float r, float g,float b,float alpha){

        this->r     = std::clamp(r,0.0f,1.0f);
        this->g     = std::clamp(g,0.0f,1.0f);
        this->b     = std::clamp(b,0.0f,1.0f);
        this->alpha = std::clamp(alpha,0.0f,1.0f);
    }
    Color Color::operator+(const Color& rhs) 
    {                           
        auto r = std::clamp(this->r+rhs.r,0.0f,1.0f);
        auto g = std::clamp(this->g+rhs.g,0.0f,1.0f);
        auto b = std::clamp(this->b+rhs.b,0.0f,1.0f);
        auto a  = std::clamp(this->alpha+rhs.alpha,0.0f,1.0f);
        return Color(r,g,b,a); // return the result by reference
    }
    
    Color& Color::operator+=(const Color& rhs) 
    {               
        *this = *this + rhs;      
        return *this; 
    }
    
    Color& Color::operator=(const Color& colorB){
        this->r = colorB.r;
        this->g = colorB.g;
        this->b = colorB.b;
        this->alpha = colorB.alpha;
        return *this;
    }

    Color operator*(const Color& color,float scalar) 
    {                           
        
        auto r = std::clamp(color.r*scalar,0.0f,1.0f);
        auto g = std::clamp(color.g*scalar,0.0f,1.0f);
        auto b = std::clamp(color.b*scalar,0.0f,1.0f);
        auto a  = std::clamp(color.alpha*scalar,0.0f,1.0f);
        return Color(r,g,b,a); // return the result by reference

    }
    
    Color operator*(float scalar,const Color& color) 
    {                           
        return color*scalar;

    }
    
    Color operator*(const Color& colorA,const Color& colorB) 
    {                           
        
        return Color(
            colorA.r*colorB.r,
            colorA.g*colorB.g,
            colorA.b*colorB.b,
            colorA.alpha*colorB.alpha
        );

    }

    Color& Color::operator*=(const Color& other) 
    {                           
        
        *this = (*this)*(other);
        return (*this);

    }

    Color operator/(const Color& color,float scalar) 
    {                           
        
        return color*(1/scalar); 
    }
    
    Color operator/(float scalar,const Color& color){
        return color*scalar;
    }
