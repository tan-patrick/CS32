#include "actor.h"
#include "StudentWorld.h"

Actor::Actor(int imageID, int startX, int startY, StudentWorld* world)
	:GraphObject(imageID, startX, startY)
{
	m_alive = true;
	m_world = world;
	setVisible(true);
}

Actor::~Actor()
{
}

bool Actor::isAlive()
{
	return m_alive;
}

void Actor::death()
{
	m_alive = false;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}

Ship::Ship(StudentWorld* world, int life)
	:Actor(IID_PLAYER_SHIP, VIEW_WIDTH/2, 1, world)
{
	m_life = 50;
}

Ship::~Ship()
{
}

void Ship::damage(int damage)
{
	/*if(type == IID_BULLET || type == IID_TORPEDO)
	{
		getWorld()->playSound(SOUND_ENEMY_PLAYER_COLLISION);
		if(type == IID_BULLET)
			m_life -= 2;
		else
			m_life -= 8;
	}*/
	m_life -= damage;
}

int Ship::getLife()
{
	return m_life;
}

PlayerShip::PlayerShip(StudentWorld* world)
	:Ship(world, 50)
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::doSomething()
{
	//isCollision
	if(getLife() <= 0)
		return;

	int key;

	if(getWorld()->getKey(key))
	{
		switch (key)
		{
			case KEY_PRESS_LEFT:
				if(getX() > 0)
					moveTo(getX() - 1, getY());
				break;
			case KEY_PRESS_RIGHT:
				if(getX() < VIEW_WIDTH - 1)
					moveTo(getX() + 1, getY());
				break;
			case KEY_PRESS_DOWN:
				if(getY() > 0)
					moveTo(getX(), getY() - 1);
				break;
			case KEY_PRESS_UP:
				if(getY() < VIEW_HEIGHT - 1)
					moveTo(getX(), getY() + 1);
				break;

				//bullet, torpedo
		}
	}

	//collision
}


Star::Star(StudentWorld* world)
	:Actor(IID_STAR, rand() % VIEW_WIDTH, VIEW_HEIGHT - 1, world)
{
}

Star::~Star()
{
}

void Star::doSomething()
{
	moveTo(getX(), getY() - 1);

	if(getY() < 0)
		death();
}