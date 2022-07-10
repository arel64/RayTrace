#include <h/Utils/RandomReal.hpp>



void RandomReal::findRandPointOnUnitSphereRadius(glm::vec3& outPoint){


    
    //normalizing random vector normally destributed;
    glm::vec3 randUnitVec(generateGaussianReal(),generateGaussianReal(),generateGaussianReal());
    //The vector now represents a point on the sphere radius at (0,0,0)
    outPoint = glm::normalize(randUnitVec);
    /*
    glm::vec3 p;
     while (true) {
         p= glm::vec3(generateRandReal(),generateRandReal(),generateRandReal());
        if (glm::dot(p,p) >= 1) continue;
        else break;    
    }
    outPoint = p;
*/
}
