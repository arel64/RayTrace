
#include <h/Render/Render.hpp>
#include <stdint.h>
#define FUNNY_MODE true
inline double getRealRand();

Render::Render(Scene& scene,uint16_t renderHeight,float ratio,uint16_t sampleSize,uint16_t antiAliasingSample,
    uint16_t maxReflections, uint16_t threadNum):
        m_scene(scene),m_height(renderHeight),m_ratio(ratio),m_sampleSize(sampleSize),
        m_maxReflections(maxReflections),m_antiAliasingSample(antiAliasingSample),m_threadNum(threadNum)
{
    m_tpool = new std::thread[threadNum];
}


void Render::startRender(sf::VertexArray* pixels,const Scene& scene){

    auto startTime = std::chrono::steady_clock::now();
    std::clog <<  "Render start" << std::endl;


    uint16_t sceneHeight    =   m_height;
    uint16_t sceneWidth     =   m_height*getRatio();
    
    
   
    uint16_t verticalClusterNum     = glm::ceil(((float)sceneWidth)/m_sampleSize);
    uint16_t horizontalClusterNum   = glm::ceil(((float)sceneHeight)/m_sampleSize);
    assert(sceneWidth>=m_sampleSize);//Add Test in constructor
    assert(sceneHeight>=m_sampleSize);


    //Create Render Queue

    SafeQueue<PixelCluster>* renderQueue = 
        new SafeQueue<PixelCluster>(verticalClusterNum*horizontalClusterNum);

    uint16_t turnucatedSampleSizeX = m_sampleSize;
    uint16_t turnucatedSampleSizeY = m_sampleSize;

    for (uint16_t i = 0; i < sceneWidth; i+=m_sampleSize)
    {
        turnucatedSampleSizeX = m_sampleSize;
        //Sample size is bigger than pixels in window in width directions
        if(i+m_sampleSize > sceneWidth){
            turnucatedSampleSizeX = sceneWidth - i; 
        }
        for (uint16_t j = 0; j < sceneHeight; j+=m_sampleSize)
        {
            turnucatedSampleSizeY = m_sampleSize;
            if(j+m_sampleSize>sceneHeight){
                turnucatedSampleSizeY = sceneHeight - j; 
            }
            renderQueue->enqueue(
                PixelCluster(i,j,turnucatedSampleSizeX,turnucatedSampleSizeY,pixels)
            );
        }
        
    }

    //Starting Rendering threads
 
    for (size_t i = 0; i < m_threadNum; i++)
    {
        m_tpool[i] = std::thread(&Render::renderQueueElements,this,renderQueue,scene);
    }
    
    for (size_t i = 0; i < m_threadNum; i++)
    {
        m_tpool[i].join();
    }
    
    auto endTime = std::chrono::steady_clock::now();
    
    
    std::clog <<  "[Render] Total: " << (endTime-startTime).count()/(1000*1000) << " ms" ;
    std::clog << "Done!";

    //Cleanup
    delete renderQueue;
    
}


void Render::colorRay(Ray &ray,const Scene& scene,RandomReal& generator){

   
    HitRecord rec;

    if(scene.hit(ray,0.0001f,std::numeric_limits<double>::infinity(),rec)){
        
        if(!rec.material->scatter(ray,rec,generator)){
            //Cannot be scattered
            ray.m_color = Color(0,0,0);
            return;
        }

        ray.m_reflectionsLeft--;
        if(ray.m_reflectionsLeft == 0){
            ray.m_color = Color(0,0,0);
            return;
        }
        //Return is needed for proper functionality
        return colorRay(ray,scene,generator);
        
    }

    glm::vec3 rayUnitDirection = glm::normalize(ray.m_direction);
    float t = 0.5*(rayUnitDirection.y + 1.0);
    //Don't forget to multiply by raycolor....
    ray.m_color = (Color(1.0, 1.0, 1.0)*(1.0-t) +Color(0.5, 0.7, 1.0)* t)*ray.m_color;
}
void Render::renderQueueElements(SafeQueue<PixelCluster>* renderQueue,const Scene scene){

    uint16_t sceneHeight    =   m_height;
    uint16_t sceneWidth     =   m_height*getRatio();

    //AA 
    uint16_t antiAliasingSample = getAntiAliasingSample();
    
    //Random Generation
    RandomReal generator(0,1);
    //Run until renderQueue is empty
    while(!renderQueue->isEmpty()){

        PixelCluster pixelCluster = renderQueue->dequeue();

        for (uint16_t j = pixelCluster.topLeftCell.y ; j <= pixelCluster.topLeftCell.y + pixelCluster.size.y -1 ; j++) {
            for (uint16_t i = pixelCluster.topLeftCell.x  ; i < pixelCluster.topLeftCell.x + pixelCluster.size.x ; i++) {

                float accumulateR,accumulateG,accumulateB;
                accumulateR=accumulateG=accumulateB=0;

                assert(antiAliasingSample>0);


                //This is for each pixel, tread lightly!
                for(uint16_t m = 0 ; m < antiAliasingSample; m++){

                    float xCoef = (float)(i+ generator.generateRandReal())/sceneWidth; 
                    float yCoef = (float)(j+ generator.generateRandReal())/sceneHeight; 

                    Ray currentPixelRay(m_maxReflections);
                    scene.getCamera().getCameraRay(xCoef,yCoef, currentPixelRay);
                    colorRay(currentPixelRay,scene,generator);
                    
                    accumulateR += currentPixelRay.m_color.r;
                    accumulateG += currentPixelRay.m_color.g;
                    accumulateB += currentPixelRay.m_color.b;

                }

                Color pixelColor(
                    accumulateR/antiAliasingSample,
                    accumulateG/antiAliasingSample,
                    accumulateB/antiAliasingSample
                );
                //pixelColor.gammaCorrect(antiAliasingSample);

                auto p = pixelColor.toSFMLColor();
                ((*pixelCluster.scenePixels)[i*sceneHeight + j]).position = sf::Vector2f(i,j);
                ((*pixelCluster.scenePixels)[i*sceneHeight + j]).color = p ;
            }
        }
    }
}