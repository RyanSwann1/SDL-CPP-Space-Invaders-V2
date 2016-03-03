#pragma once
#include <SDL.h>
#include "Entity.h"


struct Laser;
class Player :
	public Entity
{
public:
	Player();
	~Player();
	int getLives() const { return m_lives; }

	
	void movement(const MoveDirection dir);
	void shoot(std::vector<Laser>& lasers);
	void init();

private:
};

