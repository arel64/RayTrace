#include <h/Window.hpp>

Window::Window(uint16_t width,uint16_t height){
	m_scrHeight = height;
	m_scrWidth  = width;
}

void Window::openWindow(Render render){
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(m_scrWidth,m_scrHeight), "Ray Trace",sf::Style::Titlebar);
    sf::VertexArray end(sf::Points,render.getScene().getWidth()*render.getScene().getHeight());

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
        render.startRender(&end);
        window.draw(end);
        // Update the window
        window.display();
    }
}

uint16_t Window::getWindowWidth(){
	return m_scrWidth;
}

uint16_t Window::getWindowHeight(){
	return m_scrHeight;
}

float Window::getAspectRatio(){
    return static_cast<float>(m_scrWidth/m_scrHeight);
}