#include <iostream>
#include <h/Window.hpp>
#include <h/Sphere.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <memory>

int main(int, char**) {
    
	
	Scene scene(1024,720);
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0,0,-1), 0.5));
	//scene.addObject(std::make_shared<Sphere>(glm::vec3(0.3,0.3,-1), 0.3));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(0,100.5,-1), 100));
	//sample,antiAliasingSample,maxReflections,uint16_t threadNum
	Render render(scene,32,50,300);
	
	Window* window = new Window(render.getScene().getWidth(),render.getScene().getHeight());
	window->openWindow(render);
	delete window;

	return 0;

}
