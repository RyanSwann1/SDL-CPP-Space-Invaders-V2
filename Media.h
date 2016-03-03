#pragma once
#include <SDL.h>
#include "Display.h"
#include <string>
class Game;
class Display;
class Media
{
public:

	~Media();
	bool loadMedia(Display& display, Game& game);
	SDL_Texture* getPlayerTexture() const { return m_player; }
	SDL_Texture* getLaserTexture() const { return m_laser; }
	SDL_Texture* getEnemyTexture() const { return m_enemy; }
private:
	SDL_Surface* loadSurface(Game& game, Display& display, const std::string path); //Loadsurface
	SDL_Texture* loadTexture(Game& game, Display& display, const std::string path); //Loads texture

	//All textures in game
	SDL_Texture* m_enemy = nullptr;
	SDL_Texture* m_player = nullptr;
	SDL_Texture* m_laser = nullptr;
};
