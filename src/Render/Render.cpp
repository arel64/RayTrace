
#include <h/Render/Render.hpp>
#define FUNNY_MODE true
inline double getRealRand();

Render::Render(Scene& scene,uint16_t sampleSize,uint16_t antiAliasingSample,uint16_t maxReflections, uint16_t threadNum):
m_sampleSize(sampleSize),m_scene(scene),m_camera(Camera(scene.getRatio())),
m_maxReflections(maxReflections),m_antiAliasingSample(antiAliasingSample),m_threadNum(threadNum)
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




//TODO:: This whole function is temporary need to remove most parameters
void Render::rayColor(const Scene& scene,Ray &ray,RandomReal& generator,Color& outColor){
    rayColor(scene,ray,getMaxReflections(),generator,outColor);

}
void Render::rayColor(const Scene& scene,Ray &ray,uint16_t reflectionLeft,RandomReal& generator,Color& outColor){
    assert(reflectionLeft>=0);
    if(reflectionLeft == 0){
        outColor = Color(0,0,0);
        return;
    }
    HitRecord rec;

    if(scene.hit(ray,0.0001f,std::numeric_limits<double>::infinity(),rec)){
        //
        Color attenuation;
        if(!rec.material->scatter(ray,attenuation,rec,generator)){
            outColor = Color(0,0,0);
            return;
            
        }
        //assert(outColor.r==0&&outColor.g==0);
        outColor*=attenuation;

        rayColor(scene,ray,reflectionLeft-1,generator,outColor);
        return;
    }
    

    glm::vec3 rayUnitDirection = glm::normalize(ray.m_direction);
    float t = 0.5*(rayUnitDirection.y + 1.0);
    assert(t>=0&&t<=1);
    outColor = (Color(1.0, 1.0, 1.0)*(1.0-t) +Color(0.5, 0.7, 1.0)* t)*outColor;
}
void Render::renderQueueElement(SafeQueue<PixelCluster>* renderQueue,const Scene scene){
    //Scene Camera
    Camera c(scene.getRatio());
    uint16_t sceneHeight = m_scene.getHeight();
    uint16_t sceneWidth = m_scene.getWidth();

    //AA 
    uint16_t antiAliasingSample = getAntiAliasingSample();
    
    //Random Generation
    RandomReal generator(0,1);
    //Run until renderQueue is empty
    while(!renderQueue->isEmpty()){

        PixelCluster pixelCluster = renderQueue->dequeue();

        for (uint16_t j = pixelCluster.topLeftCell.y ; j <= pixelCluster.topLeftCell.y + pixelCluster.size.height -1 ; j++) {
            for (uint16_t i = pixelCluster.topLeftCell.x  ; i < pixelCluster.topLeftCell.x + pixelCluster.size.width ; i++) {

                float accumulateR,accumulateG,accumulateB;
                accumulateR=accumulateG=accumulateB=0;

                assert(antiAliasingSample>0);



                
                
                //This is for each pixel, tread lightly!
                for(uint16_t m = 0 ; m < antiAliasingSample; m++){
                    float xCoef = (float)(i+ generator.generateRandReal())/sceneWidth; 
                    float yCoef = (float)(j+ generator.generateRandReal())/sceneHeight; 
                    Ray currentPixelRay;
                    Color temp(1,1,1);
                    c.getCameraRay(xCoef,yCoef, currentPixelRay);
                    rayColor(scene,currentPixelRay,generator,temp);
                    accumulateR += temp.r;
                    accumulateG += temp.g;
                    accumulateB += temp.b;

                }

                Color pixelColor(
                    accumulateR/antiAliasingSample,
                    accumulateG/antiAliasingSample,
                    accumulateB/antiAliasingSample
                );
                auto p =pixelColor.toSFMLColor();
                ((*pixelCluster.scenePixels)[i*sceneHeight + j]).position = sf::Vector2f(i,j);
                ((*pixelCluster.scenePixels)[i*sceneHeight + j]).color = p ;
            }
        }
    }
}