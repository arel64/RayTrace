#include <cstdint>
#include <SFML/Graphics.hpp>
#include <h/Dimentions.hpp>

struct Coords{
    uint16_t x;
    uint16_t y;
    Coords(uint16_t xPos,uint16_t yPos):x(xPos),y(yPos){};
    Coords():x(0),y(0){};
};

class PixelCluster{
    
    public:
        PixelCluster(uint16_t x, uint16_t y,uint16_t width, uint16_t height
                                    ,sf::VertexArray* pixels):
        topLeftCell(x,y),scenePixels(pixels),size(width,height){};
        PixelCluster():topLeftCell(Coords()),size(Dimentions()),scenePixels(nullptr){};

        Coords topLeftCell;
        Dimentions size;
        sf::VertexArray* scenePixels;
    
};

