#pragma once

#include <SDL.h>
#include <vector>
struct Icon;
struct Laser;
class Media;
class Display;
class Entity;
class Enemy;
class Player;
class Game
{
public:
	Game();
	~Game();

	void initMenu(const Entity& player);
	void inputManager(const SDL_Event& e, Entity& player);
	void addEnemies();
	void update(Entity& player);	
	void render(const Entity& player, const Media& media);
	bool createRenderer(const Display& display);
	bool getGameOver() const { return m_gameOver; }
	void endGame() { m_gameOver = true; }
	SDL_Renderer* getRenderer() const { return m_renderer; }

private:
	SDL_Renderer* m_renderer = nullptr;

	std::vector<Icon> m_playerLivesIcons;
	std::vector<Laser> m_playerLasers;
	std::vector<Laser> m_enemyLasers;
	std::vector<Entity*> m_enemies;

	//Handles movement
	void moveEnemies();
	void moveLasers();
	void playerManagement(Entity& player);
	void playerMovementBounds(Entity& player);
	//Handles enemy shoot
	void enemyShootMananger();
	//Handles collisions
	void collisionManager(Entity& player);
	bool findEntityToLaserCollision(const Entity& entity, const Laser& laser);
	bool findEntityToEntityCollision(const Entity& player, const Entity& enemy);
	bool isGameOver(const Entity& player);
	void playerLifeDisplay(const Entity& player);

	


	bool m_gameOver = false;
	unsigned int const NUMB_OF_ENEMIES = 18;
	unsigned int m_enemyFireRate = 2000;
	unsigned const int m_enemyNextFire = 2000;

};

