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
#include "Mesh.h"

void InitScene01(Scene& scene, const Canvas& canvas);
void InitScene02(Scene& scene, const Canvas& canvas);
void AddPlane(Scene& scene, float x, float y, float z, std::string facing, color3_t color);

int main(int, char**)
{
	const int width = 400;
	const int height = 300;
	const int samples = 1;
	const int depth = 5;

	std::cout << "hell world!\n";
	color4_t color = { 0.5, 0.25, 0.75, 1 };
	rgba_t rgba = ColorToRGBA(color);
	color4_t colorAgain = RGBAToColor(rgba);


	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", width, height);

	Canvas canvas(width, height, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene scene; // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	InitScene01(scene, canvas);

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
		// render scene
		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas, samples, depth);
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}
	renderer.Shutdown();
	return 0;
}

void InitScene01(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
	scene.SetCamera(camera);

	// create objects -> add to scene
	for (int x = -10; x < 10; x++)
	{
		for (int z = -10; z < 10; z++)
		{
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			scene.AddObject(std::move(sphere));
		}
	}

	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
	scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
	float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);
	scene.SetCamera(camera);

	//auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
	//scene.AddObject(std::move(triangle));

	AddPlane(scene, 0, 0, 5, "back", { 1,1,1 });
	AddPlane(scene, 0, -1, 0, "up", { 1,1,1 });
	AddPlane(scene, 2, 0, 0, "left", { 0,1,0 });
	AddPlane(scene, -2, 0, 0, "right", { 1,0,0 });
	//AddPlane(scene, 0, 5, 0, "down", { 1,1,1 });

	auto plane = std::make_unique<Plane>(glm::vec3{ 0,5, 0 }, glm::vec3{ 0,-1,0 }, std::make_shared<Emissive>(color3_t{ 1,1,1 }));
	scene.AddObject(std::move(plane));

	auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
	mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 8 }, glm::vec3{ 0, 45, 0 });
	scene.AddObject(std::move(mesh));

}

void AddPlane(Scene& scene, float x, float y, float z, std::string facing, color3_t color)
{
	glm::vec3 normal;
	if (facing == "up") normal = { 0,1,0 };
	if (facing == "down") normal = { 0,-1,0 };
	if (facing == "left") normal = { -1,0,0 };
	if (facing == "right") normal = { 1,0,0 };
	if (facing == "back") normal = { 0,0,1 };


	auto plane = std::make_unique<Plane>(glm::vec3{ x, y, z }, normal, std::make_shared<Lambertian>(color));
	//mesh->Load("models/quad.obj", glm::vec3{ 2.0f, 1.0f, -1 }, glm::vec3{ 0, -75, 0 }, glm::vec3(2.0f));
	std::cout << plane->m_center.x << std::endl;
	std::cout << plane->m_center.y << std::endl;
	std::cout << plane->m_center.z << std::endl;
	std::cout << std::endl;
	scene.AddObject(std::move(plane));

	
}