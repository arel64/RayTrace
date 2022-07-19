#ifndef WINDOW
#define WINDOW
#include "h/Window.hpp"
#include <h/Render/Render.hpp>
#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <thread>


class Window{
    public:
        //Window(Dimentions& d): Window(d.x,d.x/d.y){};
        Window(uint16_t h,float ratio): m_scrWidth(h*ratio),m_scrHeight(h){};
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

#endif