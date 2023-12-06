#include "Renderer.h"
#include "Ray.h"
#include "Canvas.h"
#include "Random.h"
#include <iostream>
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <memory>
#include "Plane.h"
#include "Triangle.h"

int main(int, char**)
{
	std::cout << "hell world!\n";
	color4_t color = { 0.5, 0.25, 0.75, 1 };
	rgba_t rgba = ColorToRGBA(color);
	color4_t colorAgain = RGBAToColor(rgba);


	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("My Window", 400, 300);
	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene(20); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, -2 }, glm::vec3{ 1.5, 0, -2 }, glm::vec3{ 0.3, 2, -2 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	scene.AddObject(std::move(triangle));


	auto material = std::make_shared<Lambertian>(color3_t{ 0.2f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
	//scene.AddObject(std::move(plane));

	bool quit = false;

	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas,1);
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}
	renderer.Shutdown();
	return 0;
}