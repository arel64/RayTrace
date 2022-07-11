
#include <h/Window.hpp>
#ifdef WIN32
    #include <Windows.h>
#endif
Window::Window(uint16_t width,uint16_t height){
	m_scrHeight = height;
	m_scrWidth  = width;
}

void Window::openWindow(Render render){
	// Create the main window
    sf::RenderWindow window(sf::VideoMode(m_scrWidth,m_scrHeight), "Ray Trace",sf::Style::None);
    sf::VertexArray scenePixels(sf::Points,render.getScene().getSize());
    // Clear screen
    window.clear();

    std::thread renderMasterThread(&Render::startRender,render,&scenePixels,std::ref(render.getScene()));    

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                )
                window.close();
            
        }
        window.draw(scenePixels);
        // Update the window
        window.display();
        auto updateRate = std::chrono::duration<int32_t,std::milli>(5);
        std::this_thread::sleep_for(updateRate);
    }
    renderMasterThread.join();
    
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
