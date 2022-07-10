#ifndef RENDER
#define RENDER
#include <h/Scene.hpp>
#include <h/Ray.hpp>
#include <h/Dimentions.hpp>
#include <SFML/Graphics.hpp>
#include <h/Render/PixelCluster.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <h/Utils/RandomReal.hpp>
#include <h/Materials/Diffuse.hpp>
#include <chrono>
#include <iostream>
#include <thread>
class Render{

    public:
        Render(Scene& scene,uint16_t sample =32,uint16_t antiAliasingSample = 16,uint16_t maxReflections = 50,uint16_t threadNum = std::thread::hardware_concurrency());
        void startRender(sf::VertexArray*,const Scene&);
        void rayColor(const Scene& scene,Ray &ray,RandomReal& generator ,sf::Color& outColor);
        void renderQueueElement(SafeQueue<PixelCluster>* renderQueue,const Scene scene);
        uint16_t getAntiAliasingSample()const{return m_antiAliasingSample;};
        uint16_t getMaxReflections(){return m_maxReflections;};
        Scene& getScene(){return m_scene;};
    private:
        void rayColor(const Scene& scene,Ray &ray,uint16_t reflectionLeft,float factor,RandomReal& generator,sf::Color& outColor);
    private:
        Scene& m_scene;
        Camera m_camera;
        const uint16_t m_sampleSize;
        std::thread* m_tpool;
        uint16_t m_threadNum;
        const uint16_t m_antiAliasingSample; //1 Means no AntiAliasing
        const uint16_t m_maxReflections;
};
#endif