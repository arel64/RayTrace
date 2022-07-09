#include <iostream>
#include <h/Window.hpp>
#include <h/Sphere.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <memory>

int main(int, char**) {
    
	SafeQueue<int>* queue = new SafeQueue<int>(40);
	queue->enqueue(15);
	queue->enqueue(16);
	queue->enqueue(15);
	queue->dequeue();
	queue->dequeue();

	/*
	Scene scene(1280,720,1);
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0,0,-1), 0.3));
	//scene.addObject(std::make_shared<Sphere>(glm::vec3(0.3,0.3,-1), 0.3));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(0,100.5,-1), 100));
	Render render(scene);
	Window* window = new Window(render.getScene().getWidth(),render.getScene().getHeight());
	window->openWindow(render);
	delete window;
*/
	return 0;

}
