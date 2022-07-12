#include <cstdint>
#include <SFML/Graphics.hpp>
#include <h/Utils/Pair.hpp>

typedef Pair Coords;
typedef Pair Dimentions;
/**
 * @brief A block of pixels to be rendered
 * 
 */
class PixelCluster{
    
    public:
        PixelCluster():topLeftCell(Coords()),size(Dimentions()),scenePixels(nullptr){};
        PixelCluster(uint16_t x, uint16_t y,uint16_t width, uint16_t height,sf::VertexArray* pixels)
            :topLeftCell(x,y),scenePixels(pixels),size(width,height){};

    public:
        Coords              topLeftCell;
        Dimentions          size;
        sf::VertexArray*    scenePixels;
    
};

