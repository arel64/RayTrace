#ifndef RANDOM
#define RANDOM
#include <random>
#include <glm/glm.hpp>
#include <h/Sphere.hpp>
class RandomReal{
    public:
    
    RandomReal(float min,float max): 
        m_rng(m_device()),m_randUniform(min,max),m_randGauss(0,1.0f){};

    inline float    generateRandReal()      {return m_randUniform(m_rng);}
    inline float    generateGaussianReal()  {return m_randGauss(m_rng);}
    void            findRandPointOnUnitSphereRadius(glm::vec3& outPoint);


    private:
        std::random_device                      m_device;
        std::mt19937                            m_rng;
        std::uniform_real_distribution<double>  m_randUniform;
        std::normal_distribution<double>        m_randGauss;
};
#endif