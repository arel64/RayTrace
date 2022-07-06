#include <iostream>
#include <h/Window.hpp>

int main(int, char**) {
    
	Window* window = new Window(1000,500);
	window->openWindow();
	delete window;

	return 0;
}
