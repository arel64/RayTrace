#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>


class Window{
    public:
        Window(uint16_t width,uint16_t height );
        
        void openWindow();
        uint16_t getWindowWidth();
        uint16_t getWindowHeight();
    private:
    
    private:
        uint16_t scrWidth;
        uint16_t scrHeight;

};