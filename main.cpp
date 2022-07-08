#include <iostream>
#include <h/Window.hpp>
#include <h/Sphere.hpp>
#include <memory>

int main(int, char**) {
    
	Scene scene(1024,720,25);
	scene.addObject(std::make_shared<Sphere>(glm::vec3(0,0,-1), 0.3));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(0,100.5,-1), 100));
	Render render(scene);
	Window* window = new Window(render.getScene().getWidth(),render.getScene().getHeight());
	window->openWindow(render);
	delete window;

	return 0;

}
