#pragma once
#include "MoveDirection.h"
#include <SDL.h>
#include <vector>
struct Laser;
class Entity
{
public:
	Entity();
	~Entity();

	virtual void movement(const MoveDirection dir) = 0;
	virtual void shoot(std::vector<Laser>& lasers) = 0;
	virtual void init() = 0;
	void reduceLife() { m_lives--; }

	//Getters
	SDL_Rect getPosition() const { return m_pos; }
	MoveDirection getMoveDirection() const { return m_dir; }
	int getXPos() const { return m_pos.x; }
	int getYPos() const { return m_pos.y; }
	int getSizeWidth() const { return m_sizeWidth; }
	int getSizeHeight() const { return m_sizeHeight; }
	int getMovementSpeed() const { return m_movementSpeed; }
	int getfireRate() const { return m_fireRate; }
	int getNextFire() const { return m_nextFire; }
	int getLives() const { return m_lives; }
	

	//Setters
	void setPosition(int x, int y) { m_pos.x = x; m_pos.y = y; }
	void setMoveSpeed(int moveSpeed) { m_movementSpeed = moveSpeed; }
	void setSize(int width, int height) { m_pos.w = width; m_pos.h = height; }
	void setMoveDirection(MoveDirection dir) { m_dir = dir; }
	void setFireRate(int nextFire) { m_fireRate += nextFire; }

	static const int MAX_X_POS = 740;
	static const int MIN_X_POS = 0;

protected:
	
	SDL_Rect m_pos;
	unsigned int m_movementSpeed = 0;
	MoveDirection m_dir;
	//Starting pos
	unsigned int m_startXPos = 0;
	unsigned int m_startYPos = 0;
	//Size 
	unsigned int m_sizeWidth = 0;
	unsigned int m_sizeHeight = 0;
	//Rate of fire
	unsigned int m_fireRate = 0;
	unsigned int m_nextFire = 0;

	unsigned int m_lives = 0;

};

