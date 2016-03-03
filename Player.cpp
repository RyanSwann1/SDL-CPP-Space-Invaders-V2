#include "Player.h"
#include "MoveDirection.h"
#include "Laser.h"
#include <iostream>
#include <vector>


Player::Player()
{
	m_movementSpeed = 10;
	m_startXPos = 375;
	m_startYPos = 650;
	m_sizeWidth = 60;
	m_sizeHeight = 60;
	m_fireRate = 1500;
	m_nextFire = 1500;
	m_lives = 3;

	init();
}

Player::~Player()
{

}

void Player::movement(const MoveDirection dir)
{
	switch (dir)
	{
	case MoveDirection::RIGHT: 
		m_pos.x += m_movementSpeed;
		break;
		
	case MoveDirection::LEFT: 
		m_pos.x -= m_movementSpeed;
		break;
	}
}

void Player::shoot(std::vector<Laser>& lasers)
{
	//Laser size, spawn pos & movementSpeed
	int spawnXOffSet = 15;
	int spawnXPos = m_pos.x + spawnXOffSet;
	int spawnYOffset = 35;
	int spawnYPos = m_pos.y - spawnYOffset;

	lasers.push_back(Laser(spawnXPos, spawnYPos, MoveDirection::UP));
}

void Player::init()
{	
	setPosition(m_startXPos, m_startYPos);
	setMoveSpeed(m_movementSpeed);
	setSize(m_sizeWidth, m_sizeHeight);
}
