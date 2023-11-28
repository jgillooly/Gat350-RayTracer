#include "Renderer.h"
#include <iostream>

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}
void Renderer::Shutdown()
{
	if (m_window != NULL) SDL_DestroyWindow(m_window);
	if (m_renderer != NULL) SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}
bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!m_window)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	m_renderer = SDL_CreateRenderer(m_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//< create SDL renderer(https://wiki.libsdl.org/SDL2/SDL_CreateRenderer ) use flags SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC >
		if (!m_renderer)
		{
			std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}
	return true;
}