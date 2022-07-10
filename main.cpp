#include <iostream>
#include <h/Window.hpp>
#include <h/Sphere.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <memory>

int main(int, char**) {
    
	
	Scene scene(1024,720);
	/*
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-1,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.8,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.6,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-1,0.2,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-1,0.4,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.8,0.3,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-1,0.6,-1), 0.1));
	
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.2,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.2,0.2,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.2,0.4,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.2,0.6,-1), 0.1));

	scene.addObject(std::make_shared<Sphere>(glm::vec3(0.2,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0.2,0.2,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0.2,0.4,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0.2,0.6,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0,0.6,-1), 0.1));
*/
	/*
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.9,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.9,0,-1), 0.1));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-0.9,0,-1), 0.1));
	*/
	auto mat = std::make_shared<Diffuse>(0.5);
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0,0,-1), 0.5,mat));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(0,100.5,-1), 100,mat));
	//sample,antiAliasingSample,maxReflections,uint16_t threadNum
	Render render(scene,32,500,50);
	
	Window* window = new Window(render.getScene().getWidth(),render.getScene().getHeight());
	window->openWindow(render);
	delete window;

	return 0;

}
