#pragma once
#include "Entity.h"

struct Laser;
class Enemy :
	public Entity
{
public:
	Enemy();
	~Enemy();

	void movement(const MoveDirection dir);
	void shoot(std::vector<Laser>& lasers);

	
	
private:
	void init();

};

