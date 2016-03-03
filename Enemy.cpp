#include "Enemy.h"
#include "MoveDirection.h"
#include "Laser.h"

Enemy::Enemy()
{
	m_movementSpeed = 1.9;

	m_nextFire = 2000;
	m_fireRate = 2000;
	m_sizeHeight = 50;
	m_sizeWidth = 50;
}

Enemy::~Enemy()
{
}

void Enemy::movement(const MoveDirection dir)
{
	switch (dir)
	{
	case MoveDirection::LEFT: m_pos.x -= m_movementSpeed;
		break;

	case MoveDirection::RIGHT: m_pos.x += m_movementSpeed;
		break;
	}

}

void Enemy::shoot(std::vector<Laser>& lasers)
{
	//Laser size, spawn pos & movementSpeed
	int spawnXPos = m_pos.x;
	int spawnYOffset = 50;
	int spawnYPos = m_pos.y + spawnYOffset;

	lasers.push_back(Laser(spawnXPos, spawnYPos, MoveDirection::DOWN));
}

void Enemy::init()
{
}

