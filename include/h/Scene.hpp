#include <h/Camera.hpp>


class Scene{
    public:
        Scene(uint16_t width,uint16_t height) : m_width(width),m_height(height){};
        float getRatio(){return ((float)m_width)/m_height;};
        uint16_t getWidth(){return m_width;};
        uint16_t getHeight(){return m_height;};
    private:
        uint16_t m_width;
        uint16_t m_height;
};