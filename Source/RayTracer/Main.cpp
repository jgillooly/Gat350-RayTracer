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

int main(int, char**)
{
	std::cout << "hello world!\n";
	color4_t color = { 0.5, 0.25, 0.75, 1 };
	rgba_t rgba = ColorToRGBA(color);
	color4_t colorAgain = RGBAToColor(rgba);


	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("My Window", 400, 300);
	Canvas canvas(400, 300, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });

	// create objects -> add to scene
	auto sphere = std::make_unique<Sphere>(glm::vec3{ -1,-2,-4 }, 1, material);
	scene.AddObject(std::move(sphere));

	sphere = std::make_unique<Sphere>(glm::vec3{ -1,-2,-1 }, 0.5f, material);
	scene.AddObject(std::move(sphere));

	sphere = std::make_unique<Sphere>(glm::vec3{ -5,-2,-8 }, 2, material);
	scene.AddObject(std::move(sphere));

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
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}
	renderer.Shutdown();
	return 0;
}