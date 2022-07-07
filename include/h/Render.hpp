#include <h/Scene.hpp>
#include <h/Ray.hpp>
#include <SFML/Graphics.hpp>

class Render{

    public:
        Render(Scene& scene) : m_scene(scene),m_camera(Camera(scene.getRatio())) {};
        void startRender(sf::VertexArray*);
        sf::Color rayColor(const Ray &ray);
        Scene& getScene(){return m_scene;};
        //Temp
        bool hitSphere(const glm::vec3& center, double radius, const Ray& r);
    private:
        Scene& m_scene;
        Camera m_camera;
};