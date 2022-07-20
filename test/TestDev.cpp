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
TEST(DISABLED_testDev, TestViewAngle) {

	uint16_t 	renderHeight 	= 576;
	float 		renderRatio		= 16.0f/9;

	const glm::vec3& lookFrom = glm::vec3(-2,2,1);
	const glm::vec3& lookAt   = glm::vec3(0,0,-1);
	const glm::vec3& vUp      = glm::vec3(0,1,0);
	//This radius is excatly enough for the edges of the Sphere to touch the top of the window.	
	Camera cam(renderRatio,90.0f,lookFrom, lookAt, vUp);
	//Camera cam(renderRatio,90.0f);
	Scene scene(renderRatio,cam);
	
	
	
	auto material_ground 	= new Diffuse(Color(0.8, 0.8, 0.0));
	auto material_center 	= new Diffuse(Color(0.1, 0.2, 0.5));
	auto material_left   	= new Dielectric(1.5);
	auto material_right  		= new Metal(Color(0.8, 0.6, 0.2), 0.0);

	scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
	scene.addObject(std::make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.0),   0.5, material_center));
	scene.addObject(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, material_left));
	//scene.addObject(std::make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0), -0.45, material_left));
	scene.addObject(std::make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, material_right));

	

	Render render(scene,renderHeight,renderRatio,32,100,200);
	Window* window = new Window(renderHeight,renderRatio);
	window->openWindow(render);


	delete material_left;
	delete material_right;

	delete window;

    EXPECT_TRUE(true);
}

TEST(DISABLED_testDev, TestDetectRatio) {

	uint16_t 	renderHeight 	= 576;
	float 		renderRatio		= 16.0f/9;
	//This radius is excatly enough for the edges of the Sphere to touch the top of the window.	
	auto R = 0.707106781f;

	Camera cam(renderRatio,90.0f);
	Scene scene(renderRatio,cam);


    auto material_left  = new Diffuse(Color(0,0,1));
    auto material_right = new Diffuse(Color(1,0,0));

    scene.addObject(std::make_shared<Sphere>(glm::vec3(-R, 0, -1), R, material_left));
    scene.addObject(std::make_shared<Sphere>(glm::vec3( R, 0, -1), R, material_right));

    // Camera

    Render render(scene,renderHeight,renderRatio,32,100,200);
	Window* window = new Window(renderHeight,renderRatio);
	window->openWindow(render);


	delete material_left;
	delete material_right;

	delete window;

    EXPECT_TRUE(true);
}