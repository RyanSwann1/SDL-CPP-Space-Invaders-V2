#pragma once
#include <SDL.h>
struct Icon
{
	Icon(SDL_Rect pos)
	{
		m_pos = pos;
	}
	SDL_Rect m_pos;
};