#include "Renderer.h"
#include <iostream>

int main(int, char**)
{
	std::cout << "hello world!\n";
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("My Window", 400, 300);
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
	}
	renderer.Shutdown();
	return 0;
}