
#include <h/Window.hpp>

Window::Window(uint16_t width,uint16_t height){
	m_scrHeight = height;
	m_scrWidth  = width;
}

void Window::openWindow(Render render){
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(m_scrWidth,m_scrHeight), "Ray Trace",sf::Style::Titlebar | sf::Style::Close);
    sf::VertexArray scenePixels(sf::Points,render.getScene().getSize());

    // Clear screen
    window.clear();
    render.startRender(&scenePixels,render.getScene());
    window.draw(scenePixels);
    // Update the window
    window.display();

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
