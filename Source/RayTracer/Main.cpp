#include "Renderer.h"
#include "Ray.h"
#include "Canvas.h"
#include "Random.h"
#include <iostream>

int main(int, char**)
{
	std::cout << "hello world!\n";
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("My Window", 400, 300);
	Canvas canvas(400, 300, renderer);
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
		for (int i = 0; i < 1000; i++) { 
			canvas.DrawPoint({ random01() * canvas.GetSize().x, random01() * canvas.GetSize().y }, { random01(),random01(),random01(),1 });
		}

		//canvas.DrawPoint({ 1 * canvas.GetSize().x, 1 * canvas.GetSize().y }, { 1,1,1,1 });

		canvas.Update();

		renderer.PresentCanvas(canvas);
	}
	renderer.Shutdown();
	return 0;
}