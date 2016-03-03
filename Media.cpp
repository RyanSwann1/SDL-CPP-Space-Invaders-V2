#include "Media.h"
#include "Game.h"


SDL_Surface* Media::loadSurface(Game& game, Display& display, const std::string path)
{
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (surface == nullptr)
	{
		printf("Failed to load texture", path.c_str());
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(surface, display.getWindowSurface()->format, 0);
	}
	SDL_FreeSurface(surface);
	return optimizedSurface;
}

SDL_Texture* Media::loadTexture(Game& game, Display& display, const std::string path)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game.getRenderer(), loadSurface(game, display, path.c_str()));
	if (texture == nullptr)
	{
		printf("Failed to load ", path.c_str());
	}

	return texture;
}

Media::~Media()
{
	SDL_DestroyTexture(m_enemy);
	SDL_DestroyTexture(m_player);
	SDL_DestroyTexture(m_laser);
	m_enemy = nullptr;
	m_player = nullptr;
	m_laser = nullptr;
}

bool Media::loadMedia(Display& display, Game& game)
{
	bool success = true;
	m_enemy = loadTexture(game, display, "enemy.bmp");
	if (m_enemy == nullptr)
	{
		printf("Failed to load enemy.");
		success = false;
	}

	m_player = loadTexture(game, display, "player.bmp");
	if (m_player == nullptr)
	{
		printf("Failed to load player");
		success = false;
	}

	m_laser = loadTexture(game, display, "laser.bmp");
	if (m_player == nullptr)
	{
		printf("Failed to load laser.");
		success = false;
	}
	return success;
}
