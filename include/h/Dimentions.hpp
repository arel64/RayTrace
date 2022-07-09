#ifndef DIMENTIONS
#define DIMENTIONS
#include <cstdint>
struct Dimentions{
    uint16_t height;
    uint16_t width;
    Dimentions(uint16_t width,uint16_t height):width(width),height(height){};
    Dimentions(): height(0),width(0){};
}typedef Dimentions;

#endif