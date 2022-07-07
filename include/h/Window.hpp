
#include <h/Render.hpp>
#include <iostream>
#include <cstdint>


struct Dimentions{
    uint16_t height;
    uint16_t width;
}typedef Dimentions;

class Window{
    public:
        Window(Dimentions& d): m_scrHeight(d.height),m_scrWidth(d.width) {};
        Window(uint16_t,uint16_t);
        void openWindow(Render);
        uint16_t getWindowWidth();
        uint16_t getWindowHeight();
        float    getAspectRatio();
    public:
  //      static constexpr float FHD = 16/9.0f;
    private:
        uint16_t m_scrWidth;
        uint16_t m_scrHeight;

};

