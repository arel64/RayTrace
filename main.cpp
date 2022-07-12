#include "main.hpp"
int main(int, char**) {
    
	Scene scene(1024,720);


	Diffuse* material_ground 	= new Diffuse(Color(0.8, 0.8, 0.0));
	Dielectric* material_center   		= new Dielectric(1.5);
    Dielectric* material_left     		= new Dielectric(1.5);
    Metal* material_right  		= new Metal(Color(0.8, 0.6, 0.2),1.0f);

    scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, material_right));


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
