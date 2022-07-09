#ifndef RENDER
#define RENDER
#include <h/Scene.hpp>
#include <h/Ray.hpp>
#include <h/Dimentions.hpp>
#include <SFML/Graphics.hpp>
#include <h/PixelCluster.hpp>
#include <chrono>
#include <iostream>
#include <random>
class Render{

    public:
        Render(Scene& scene) : m_scene(scene),m_camera(Camera(scene.getRatio())) {};
        void startRender(sf::VertexArray*,const Scene&);
        void rayColor(const Scene& scene,const Ray &ray,sf::Color& outColor);
        Scene& getScene(){return m_scene;};
        
    private:
        Scene& m_scene;
        Camera m_camera;
};
#endif