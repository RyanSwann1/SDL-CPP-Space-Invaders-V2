#include "Game.h"
#include "Entity.h"
#include "MoveDirection.h"
#include "Laser.h"
#include "Media.h"
#include "Display.h"
#include "Enemy.h"
#include "Icon.h"
#include "Player.h"
#include <iostream>


Game::Game()
{
	
}

Game::~Game()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i] = nullptr;
	}
}

void Game::initMenu(const Entity& player)
{
	int startXPos = 25;
	int startYPos = 700;
	int newXPos = 50;
	const int playerTextureSizeWidth = 20;
	const int playerTextureSizeHeight = 20;
	for (int i = 0; i < player.getLives(); i++)
	{
		m_playerLivesIcons.push_back(Icon({ startXPos, startYPos, playerTextureSizeWidth, playerTextureSizeHeight }));
		startXPos += newXPos;
	}
}

void Game::inputManager(const SDL_Event& e, Entity& player )
{
	switch (e.key.keysym.sym)
	{
	case SDLK_d: player.movement(MoveDirection::RIGHT);
		break;
	case SDLK_a: player.movement(MoveDirection::LEFT);
		break;
	case SDLK_SPACE: 
	{
		int currentTime = SDL_GetTicks();
		if (SDL_TICKS_PASSED(currentTime, player.getfireRate()))
		{
			player.shoot(m_playerLasers);
			player.setFireRate(player.getNextFire());
			break;
		}
	}
	}
}

bool Game::createRenderer(const Display& display)
{
	bool success = true;
	m_renderer = SDL_CreateRenderer(display.getWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		success = false;
	}
	return success;
}

void Game::render(const Entity& player, const Media& media)
{
	SDL_RenderClear(m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 0); //Background

	//Render player
	SDL_RenderCopy(m_renderer, media.getPlayerTexture(), nullptr, &player.getPosition());
	
	//Render player lasers
	for (auto &laser : m_playerLasers)
	{
		SDL_RenderCopy(m_renderer, media.getLaserTexture(), nullptr, &laser.m_pos);
	}

	//Render enemy lasers
	for (auto &laser : m_enemyLasers)
	{
		SDL_RenderCopy(m_renderer, media.getLaserTexture(), nullptr, &laser.m_pos);
	}

	//Render enemies
	for (auto &enemy : m_enemies)
	{
		SDL_RenderCopy(m_renderer, media.getEnemyTexture(), nullptr, &enemy->getPosition());
	}

	////Render Icons
	for (auto &playerLifeIcon : m_playerLivesIcons)
	{
		SDL_RenderCopy(m_renderer, media.getPlayerTexture(), nullptr, &playerLifeIcon.m_pos);
	}

	//Apply render
	SDL_RenderPresent(m_renderer);
}

void Game::update(Entity& player)
{
	enemyShootMananger();

	moveLasers();
	moveEnemies();

	playerManagement(player);

	
	//Collisions
	collisionManager(player);

	//Check to see whether game is over or not
	m_gameOver = isGameOver(player);
}


void Game::addEnemies()
{
	int startXPos = 100;
	int startYPos = 100;
	int newXPos = 100;
	int newYPos = 100;
	//Spawn all enemies
	for (unsigned int i = 0; i < NUMB_OF_ENEMIES; i++)
	{
		//Initialize Enemy
		Entity *enemy = new Enemy(); //Being assigned onto the heap - Computers RAM - 
		enemy->setPosition(startXPos, startYPos);
		enemy->setSize(enemy->getSizeWidth(), enemy->getSizeHeight());
		enemy->setMoveSpeed(enemy->getMovementSpeed());
		enemy->setMoveDirection(MoveDirection::LEFT);
		//Add enemy to data structure
		m_enemies.push_back(enemy);
		startXPos += newXPos;
		if (i == 5 || i == 11)
		{
			startYPos += newYPos;
			startXPos = 100;
		}
		//After every enemy spawned, move along the row
		/*
		Javawag: only thing that would explain that error lol
		Javawag: soooo the compiler is basically saying okay you have a Enemy &, i need to make it into a Entity &... ooh so i create a new Entity and copy over all the members in Entity (m_pos, the other one) using the values in your Enemy you passed in
		Javawag: and then it goes woah shit one cannot simply create an Entity
		Javawag: so! to solve this
		Javawag: change your vector to hold Entity *, so std::vector<Entity *> - and then change your push_back to not have the * before enemy
		Javawag: that way the compiler just copies the pointer value, not trying to mess around with your enemies making them into entities :D
		*/
	}
}


void Game::moveLasers()
{
	//Movement of player lasers
	for (auto & laser : m_playerLasers)
	{	
		if (laser.m_dir == MoveDirection::UP)
		{
			laser.m_pos.y -= laser.m_movementSpeed;
		}
	}
	//Movement of enemy lasers
	for (auto &laser : m_enemyLasers)
	{
		if (laser.m_dir == MoveDirection::DOWN)
		{
			laser.m_pos.y += laser.m_movementSpeed;
		}
	}
}

void Game::playerManagement(Entity & player)
{
	playerMovementBounds(player);
	playerLifeDisplay(player);
}

void Game::playerMovementBounds(Entity& player)
{
	if (player.getPosition().x <= Entity::MIN_X_POS) 
	{
		int currentYPos = player.getPosition().y;
		player.setPosition(Entity::MIN_X_POS, currentYPos);
	}

	if (player.getPosition().x >= Entity::MAX_X_POS) 
	{
		int currentYPos = player.getPosition().y;
		player.setPosition(Entity::MAX_X_POS, currentYPos);
	}
}

void Game::enemyShootMananger()
{
	//If enemies are still in game
	if (m_enemies.size() > 0)
	{
		int randEnemy = rand() % m_enemies.size(); //Select random enemy
		int currentTime = SDL_GetTicks();
		if (SDL_TICKS_PASSED(currentTime, m_enemyFireRate))
		{
			m_enemies[randEnemy]->shoot(m_enemyLasers);
			m_enemyFireRate += m_enemyNextFire;
		}
	}
}

void Game::moveEnemies()
{
	const int NEW_YPOS = 20; //After enemy hits wall, move down 
	for (auto &enemy : m_enemies)
	{
		//Move Left
		if (enemy->getMoveDirection() == MoveDirection::LEFT)
		{
			enemy->movement(MoveDirection::LEFT);
			if (enemy->getPosition().x < Entity::MIN_X_POS)
			{
				int currentYPos = enemy->getPosition().y;
				enemy->setPosition(Entity::MIN_X_POS, currentYPos);
				//Change movement direction of all enemies
				for (auto &i : m_enemies)
				{
					int currentYPos = i->getPosition().y;
					int currentXPos = i->getPosition().x;
					i->setPosition(currentXPos, currentYPos + NEW_YPOS);
					i->setMoveDirection(MoveDirection::RIGHT);
				}
			}
		}
		//Move Right
		if (enemy->getMoveDirection() == MoveDirection::RIGHT)
		{
			enemy->movement(MoveDirection::RIGHT);
			if (enemy->getPosition().x > Entity::MAX_X_POS)
			{
				int currentYPos = enemy->getPosition().y;
				enemy->setPosition(Entity::MAX_X_POS, currentYPos);
				//Change all enemies movement direction
				for (auto &i : m_enemies)
				{
					int currentYPos = i->getPosition().y;
					int currentXPos = i->getPosition().x;
					i->setPosition(currentXPos, currentYPos + NEW_YPOS);
					i->setMoveDirection(MoveDirection::LEFT);
				}
			}
		}
	}
}

void Game::collisionManager(Entity& player)
{
	////Search for playerLaser collisions
	for (unsigned int playerLaser = 0; playerLaser < m_playerLasers.size(); playerLaser++)
	{
		for (unsigned int enemy = 0; enemy < m_enemies.size(); enemy++)
		{
			//Collision found
			if (findEntityToLaserCollision(*m_enemies[enemy], m_playerLasers[playerLaser]))
			{
				m_enemies.erase(m_enemies.begin() + enemy); //Remove enemy
				m_playerLasers.erase(m_playerLasers.begin() + playerLaser); //Remove player laser
				return;
			}

		}
	}

	//Find Enemy laser/Player collisiion
	for (unsigned int enemyLaser = 0; enemyLaser < m_enemyLasers.size(); enemyLaser++)
	{
		//Collision Found
		if (findEntityToLaserCollision(player, m_enemyLasers[enemyLaser]))
		{
			player.reduceLife();
			m_enemyLasers.erase(m_enemyLasers.begin() + enemyLaser);
			return;
		}
	}
	
	//Find Player to Enemy Collision
	for (unsigned int enemy = 0; enemy < m_enemies.size(); enemy++)
	{
		if (findEntityToEntityCollision(player, *m_enemies[enemy]))
		{
			player.reduceLife();
		}
	}
}

bool Game::findEntityToLaserCollision(const Entity& entity, const Laser& laser)
{
	//Check left of entity
	if (entity.getXPos() > (laser.m_pos.x + laser.SIZE_WIDTH)) {
		return false;
	}
	//Check right of entity
	if ((entity.getXPos() + entity.getSizeWidth()) < laser.m_pos.x){
		return false;
	}
	//Check top of entity
	if (entity.getYPos() > (laser.m_pos.y + laser.SIZE_HEIGHT)) {
		return false;
	}
	if ((entity.getYPos() + entity.getSizeHeight()) < laser.m_pos.y) {
		return false;
	}
	
	return true;
}

bool Game::findEntityToEntityCollision(const Entity & player, const Entity& enemy)
{
	//Check left of entity
	if (player.getXPos() > (enemy.getXPos() + enemy.getSizeWidth())) {
		return false;
	}
	//Check right of entity
	if ((player.getXPos() + player.getSizeWidth()) < enemy.getXPos()) {
		return false;
	}
	//Check top of entity
	if (player.getYPos() > (enemy.getYPos() + enemy.getSizeWidth())) {
		return false;
	}
	//Check bottom of entity
	if ((player.getYPos() + player.getSizeHeight()) < enemy.getYPos()) {
		return false;
	}
	//if no collision
	return true;
}

bool Game::isGameOver(const Entity& player)
{
	if (m_enemies.size() <= 0) {
		return true;
	}
	if (player.getLives() <= 0) {
		return true;
	}
	return false;
}

void Game::playerLifeDisplay(const Entity& player)
{
	m_playerLivesIcons.clear();
	int startXPos = 25;
	int startYPos = 700;
	int newXPos = 50;
	const int playerTextureSizeWidth = 20;
	const int playerTextureSizeHeight = 20;
	for (int i = 0; i < player.getLives(); i++)
	{
		m_playerLivesIcons.push_back(Icon({ startXPos, startYPos, playerTextureSizeWidth, playerTextureSizeHeight }));
		startXPos += newXPos;
	}
}
