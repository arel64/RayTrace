#ifndef RENDER
#define RENDER
#include <h/Scene.hpp>
#include <h/Ray.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
class Render{

    public:
        Render(Scene& scene) : m_scene(scene),m_camera(Camera(scene.getRatio())) {};
        void startRender(sf::VertexArray*,const Scene&);
        sf::Color rayColor(const Scene& scene,const Ray &ray);
        Scene& getScene(){return m_scene;};
    private:
        Scene& m_scene;
        Camera m_camera;
};
#endif