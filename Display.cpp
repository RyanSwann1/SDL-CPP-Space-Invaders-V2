#include "Display.h"
#include "Entity.h"
#include "Media.h"
#include "Laser.h"
#include <iostream>


Display::~Display()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
}

bool Display::init()
{
	bool success = true;
	//Initialize SDL Video
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
		printf("Video failed to initialize.", SDL_GetError());
	}
	else
	{
		//Create Window
		m_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE_W, WINDOW_SIZE_W, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			success = false;
			printf("Failed to create window.", SDL_GetError());
		}
		else
		{
			//Get the window surface
			m_windowSurface = SDL_GetWindowSurface(m_window);
			if (m_windowSurface == nullptr)
			{
				success = false;
				printf("Failed to get the window surface.", SDL_GetError());
			}
		}
	}
	return success;
}
