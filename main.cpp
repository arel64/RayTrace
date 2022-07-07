#include <iostream>
#include <h/Window.hpp>
int main(int, char**) {
    
	Scene scene(1280,720);
	Render render(scene);
	Window* window = new Window(render.getScene().getWidth(),render.getScene().getHeight());
	window->openWindow(render);
	delete window;

	return 0;
}
