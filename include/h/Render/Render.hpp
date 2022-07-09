#ifndef RENDER
#define RENDER
#include <h/Scene.hpp>
#include <h/Ray.hpp>
#include <h/Dimentions.hpp>
#include <SFML/Graphics.hpp>
#include <h/Render/PixelCluster.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
class Render{

    public:
        Render(Scene& scene,uint16_t sample =32,uint16_t threadNum = std::thread::hardware_concurrency());
        void startRender(sf::VertexArray*,const Scene&);
        void rayColor(const Scene& scene,const Ray &ray,sf::Color& outColor);
        void renderQueueElement(SafeQueue<PixelCluster>* renderQueue,const Scene& scene);
        Scene& getScene(){return m_scene;};
        
    private:
        Scene& m_scene;
        Camera m_camera;
        const uint16_t m_sampleSize;
        std::thread* m_tpool;
        uint16_t m_threadNum;
};
#endif