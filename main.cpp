#include "main.hpp"
#include <h/Utils/Color.hpp>
int main(int, char**) {
    
	
	Scene scene(1024,720);


	Diffuse* material_ground 	= new Diffuse(Color(0.8, 0.8, 0.0));
	Diffuse* material_center 	= new Diffuse(Color(0.7, 0.3, 0.3));
    Metal* material_left   		= new Metal(Color(0.8, 0.8, 0.8));
    Metal* material_right  		= new Metal(Color(0.8, 0.6, 0.2));

    scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, material_right));


	//sample,antiAliasingSample,maxReflections,uint16_t threadNum
	Render render(scene,32,100,200);
	Window* window = new Window(render.getScene().getWidth(),render.getScene().getHeight());
	window->openWindow(render);



	delete material_ground;
	delete material_center;
	delete material_left;
	delete material_right;

	delete window;

	return 0;

}
