#ifndef DIMENTIONS
#define DIMENTIONS
#include <cstdint>
/**
 * @brief Pair of ints
 * 
 */
struct Pair{
    uint16_t x;
    uint16_t y;
    Pair(uint16_t x,uint16_t y):x(x),y(y){};
    Pair(): x(0),y(0){};
}typedef Pair;

#endif