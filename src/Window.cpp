
#include <h/Window.hpp>

Window::Window(uint16_t width,uint16_t height){
	scrHeight = height;
	scrWidth  = width;
}

void Window::openWindow(){
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(scrWidth,scrHeight), "Ray Trace");

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();

        // Draw the sprite
        for (int j = scrHeight-1; j >= 0; --j) {
            for (int i = 0; i < scrWidth; ++i) {
                auto r = double(i) / (scrWidth-1);
                auto g = double(j) / (scrHeight-1);
                auto b = 0.25;

                int ir = static_cast<int>(255.999 * r);
                int ig = static_cast<int>(255.999 * g);
                int ib = static_cast<int>(255.999 * b);
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(1, 1));
                rectangle.setFillColor(sf::Color(ir,ig,ib,255));
                rectangle.setPosition(r,g);
                window.draw(rectangle);
            }
        }
     
        // Update the window
        window.display();
    }
}

uint16_t Window::getWindowWidth(){
	return scrWidth;
}

uint16_t Window::getWindowHeight(){
	return scrHeight;
}
