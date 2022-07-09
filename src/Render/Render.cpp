
#include <h/Render/Render.hpp>
#define FUNNY_MODE true
inline double getRealRand();

Render::Render(Scene& scene,uint16_t sampleSize, uint16_t threadNum):
m_sampleSize(sampleSize),m_scene(scene),m_camera(Camera(scene.getRatio())),m_threadNum(threadNum)
{
    m_tpool = new std::thread[threadNum];
}


void Render::startRender(sf::VertexArray* pixels,const Scene& scene){

    auto startTime = std::chrono::steady_clock::now();
    
    std::clog <<  "Render start" << std::endl;
    uint16_t sceneHeight = m_scene.getHeight();
    uint16_t sceneWidth = m_scene.getWidth();
    //Load render queue
    uint16_t verticalClusterNum     = glm::ceil(((float)sceneWidth)/m_sampleSize);
    uint16_t horizontalClusterNum   = glm::ceil(((float)sceneHeight)/m_sampleSize);
    SafeQueue<PixelCluster>* renderQueue = new SafeQueue<PixelCluster>(verticalClusterNum*horizontalClusterNum);

    assert(sceneWidth>=m_sampleSize);
    assert(sceneHeight>=m_sampleSize);

    for (uint16_t i = 0; i < sceneWidth; i+=m_sampleSize)
    {
        uint16_t turnucatedSampleSizeX = m_sampleSize;
        if(i+m_sampleSize>sceneWidth){
            turnucatedSampleSizeX = sceneWidth - i; 
        }
        for (uint16_t j = 0; j < sceneHeight; j+=m_sampleSize)
        {
            uint16_t turnucatedSampleSizeY = m_sampleSize;
            if(j+m_sampleSize>sceneHeight){
                turnucatedSampleSizeY = sceneHeight - j; 
            }
            renderQueue->enqueue(
                PixelCluster(i,j,turnucatedSampleSizeX,turnucatedSampleSizeY,pixels)
            );
        }
        
    }
    //Start rendering threads
 
    for (size_t i = 0; i < m_threadNum; i++)
    {
        m_tpool[i] = std::thread(&Render::renderQueueElement,this,
        renderQueue,scene);
    }
    
    for (size_t i = 0; i < m_threadNum; i++)
    {
        m_tpool[i].join();
    }
    auto endTime = std::chrono::steady_clock::now();
    delete renderQueue;
    std::clog <<  "[Render] Total: " << (endTime-startTime).count()/(1000*1000) << " ms" ;
    std::clog << "Done!";
}




//TODO:: This whole function is temporary
void Render::rayColor(const Scene& scene,const Ray &ray,sf::Color& outColor){
    HitRecord rec;

    if(scene.hit(ray,0.0f,std::numeric_limits<double>::infinity(),rec)){
        glm::vec3 rayNormalAt = glm::normalize(ray.at(rec.t) - glm::vec3(0,0,-1));
        
        outColor.r =255;
        outColor.g =glm::abs(rayNormalAt.z)*255;
        outColor.b =255;
        return;
    }
    

    glm::vec3 rayNormDirection = glm::normalize(ray.m_direction);
    float t = 0.5*(rayNormDirection.y + 1.0);

    outColor.r =255*(1.0-t) + t*0.1*255;
    outColor.g =255*(1.0-t) + t*0.7*255;
    outColor.b =255*(1.0-t) + t* 1.0*255;
}

void Render::renderQueueElement(SafeQueue<PixelCluster>* renderQueue,const Scene scene){

    //Scene Camera
    Camera c(scene.getRatio());
    uint16_t sceneHeight = m_scene.getHeight();
    uint16_t sceneWidth = m_scene.getWidth();

    //AA 
    uint16_t antiAliasingSample =scene.getAntiAliasingSample();
    
    //Random Generation
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> rand(0.0,1.0);

    //Run until renderQueue is empty
    while(!renderQueue->isEmpty()){

        PixelCluster pixelCluster = renderQueue->dequeue();

        for (uint16_t j = pixelCluster.topLeftCell.y ; j <= pixelCluster.topLeftCell.y + pixelCluster.size.height -1 ; j++) {
            for (uint16_t i = pixelCluster.topLeftCell.x  ; i < pixelCluster.topLeftCell.x + pixelCluster.size.width ; i++) {

                uint32_t accumulateR,accumulateG,accumulateB;
                accumulateR=accumulateG=accumulateB=0;

                assert(antiAliasingSample>0);



                sf::Color temp;
                Ray currentPixelRay;
                //This is for each pixel, tread lightly!
                for(uint16_t m = 0 ; m < antiAliasingSample; m++){
                    float xCoef = (float)(i+ rand(rng))/sceneWidth; 
                    float yCoef = (float)(j+ rand(rng))/sceneHeight; 
                    c.getCameraRay(xCoef,yCoef, currentPixelRay);
                    
                    rayColor(scene,currentPixelRay,temp);
                    
                    accumulateR += temp.r;
                    accumulateG += temp.g;
                    accumulateB += temp.b;

                }
                sf::Color pixelColor(
                    accumulateR/antiAliasingSample,
                    accumulateG/antiAliasingSample,
                    accumulateB/antiAliasingSample
                );
            
                ((*pixelCluster.scenePixels)[i*sceneHeight + j]).position = sf::Vector2f(i,j);
                ((*pixelCluster.scenePixels)[i*sceneHeight + j]).color =  pixelColor;

            }
        }
    }
}