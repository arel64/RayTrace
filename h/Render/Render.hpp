#ifndef RENDER
#define RENDER
#include <h/Scene.hpp>
#include <h/Ray.hpp>
#include <SFML/Graphics.hpp>
#include <h/Render/PixelCluster.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <h/Utils/RandomReal.hpp>
#include <h/Utils/Color.hpp>
#include <h/Materials/Diffuse.hpp>
#include <chrono>
#include <iostream>
#include <thread>

class Render{

    public:
        Render(Scene& scene,uint16_t sample =32,uint16_t antiAliasingSample = 16,uint16_t maxReflections = 50,uint16_t threadNum = std::thread::hardware_concurrency());
        
        void        startRender(sf::VertexArray*,const Scene&);
        void        colorRay(Ray&, const Scene& ,RandomReal&);
        void        renderQueueElements(SafeQueue<PixelCluster>*,const Scene);


        uint16_t    getAntiAliasingSample()const{return m_antiAliasingSample;};
        uint16_t    getMaxReflections(){return m_maxReflections;};
        Scene&      getScene(){return m_scene;};
    
    private:

        Scene&          m_scene;
        Camera          m_camera;
        
        std::thread*    m_tpool;
        uint16_t        m_threadNum;

        const uint16_t  m_sampleSize;
        const uint16_t  m_antiAliasingSample; 
        const uint16_t  m_maxReflections;
};
#endif