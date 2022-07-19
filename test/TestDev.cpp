#include "h/Camera.hpp"
#include <glm/ext/scalar_constants.hpp>
#include <glm/trigonometric.hpp>
#include <gtest\gtest.h>
#include <h/Window.hpp>
#include <h/Sphere.hpp>
#include <h/Utils/SafeQueue.hpp>
#include <h/Materials/Metal.hpp>
#include <h/Materials/Diffuse.hpp>
#include <h/Materials/Dielectric.hpp>
#include <h/Utils/Color.hpp>
#include <glm/gtc/constants.hpp>
#include <stdint.h>

TEST(DISABLED_testDev, TestFullRender) {
	
	uint16_t 	renderHeight 	= 576;
	float 		renderRatio		= 16.0f/9;
	
	float radius 		= glm::cos(glm::degrees(glm::pi<float>()/4));
	
	
	auto camera = Camera(renderRatio,90.0f);
    Scene scene(renderRatio,camera);


	Diffuse* material_ground 	= new Diffuse(Color(0.8, 0.8, 0.0));
	Dielectric* material_center = new Dielectric(1.5);
    Dielectric* material_left   = new Dielectric(1.5);
    Metal* material_right  		= new Metal(Color(0.8, 0.6, 0.2),1.0f);
	
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    scene.addObject(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, material_right));


	Render render(scene,renderHeight,renderRatio,32,100,200);
	Window* window = new Window(renderHeight,renderRatio);
	window->openWindow(render);



	delete material_ground;
	delete material_center;
	delete material_left;
	delete material_right;

	delete window;

    EXPECT_TRUE(true);
}
TEST(DISABLED_testDev, TestCameraRender) {

	uint16_t 	renderHeight 	= 576;
	float 		renderRatio		= 16.0f/9;
	//This radius is excatly enough for the edges of the Sphere to touch the top of the window.	
	float radius 		= 0.707106781f;
	auto camera = Camera(renderRatio,90.0f);
    Scene scene(renderRatio,camera);
	
	

	auto material_left  = new Diffuse(Color(0,0,1));
    auto material_right = new Diffuse(Color(1,0,0));

    scene.addObject(std::make_shared<Sphere>(glm::vec3(-radius, 0, -1), radius, material_left));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( radius, 0, -1), radius, material_right));

	Render render(scene,renderHeight,renderRatio,32,100,200);
	Window* window = new Window(renderHeight,renderRatio);
	window->openWindow(render);


	delete material_left;
	delete material_right;

	delete window;

    EXPECT_TRUE(true);
}