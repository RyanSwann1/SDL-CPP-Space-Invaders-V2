#pragma once
#include <SDL.h>
#include "MoveDirection.h"
struct Laser
{
	Laser(int spawnXPos, int spawnYPos, MoveDirection dir)
	{
		m_pos.x = spawnXPos;
		m_pos.y = spawnYPos;
		m_pos.h = SIZE_HEIGHT;
		m_pos.w = SIZE_WIDTH;
		m_movementSpeed = MOVEMENT_SPEED;
		m_dir = dir;
	}
	SDL_Rect m_pos;
	int m_movementSpeed = 0;
	MoveDirection m_dir;

	//Size & Movement speed of laser
	int SIZE_WIDTH = 30;
	int SIZE_HEIGHT = 30;
	int MOVEMENT_SPEED = 3;
};