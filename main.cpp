#include "Display.h"
#include "Media.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "MoveDirection.h"
#include "Game.h"

#include <SDL.h>
#include <iostream>

void quit(Display& display, Game& game, Media& media)
{
	display.~Display();
	game.~Game();
	media.~Media();
	printf("\nGame Ended.");

	SDL_Quit();
}

bool init(Display& display, Game& game, Media& media)
{
	bool success = true;

	//Initialize SDL Video
	if (!display.init()) {
		printf("Failed to initialize SDL Video");
		success = false;
	}

	if (!game.createRenderer(display))
	{
		printf("Failed to create the renderer.");
		success = false;
	}

	//Intiailize/Load media
	if (!media.loadMedia(display, game)) {
		printf("Failed to load media");
		success = false;
	}

	return success;
}

int main(int argc, char* args[])
{
	//Stack
	Display display;
	Game game;
	Media media;
	bool gameOngoing = true;

	gameOngoing = init(display, game, media);

	//Game Begin
	if (gameOngoing) 
	{
		printf("Begin game loop");

		SDL_Event e;

		//Heap
		Entity* player = new Player();

		game.initMenu(*player);
		game.addEnemies();

		//Begin game loop
		while (!game.getGameOver())
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) {
					game.endGame();
				}
				if (e.type == SDL_KEYDOWN) {
					game.inputManager(e, *player);
				}
				
			}

			game.update(*player);
			game.render(*player, media);

			SDL_Delay(16);
		}
	}
	else
	{
		SDL_Delay(4000);
	}
	
	quit(display, game, media);

	char c;
	std::cin >> c;

	return 0;
}