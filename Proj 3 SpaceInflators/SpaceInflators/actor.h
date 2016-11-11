#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, int startX, int startY, StudentWorld* world);
	~Actor();
	virtual void doSomething() = 0;
	bool isAlive();
	void death();
	StudentWorld* getWorld();
private:
	bool m_alive;
	StudentWorld* m_world;
};

class Ship : public Actor
{
public:
	Ship(StudentWorld* world, int life);
	~Ship();
	virtual void doSomething() = 0;
	void damage(int type);
	int getLife();
private:
	int m_life;
};

class PlayerShip : public Ship
{
public:
	PlayerShip(StudentWorld* world);
	~PlayerShip();
	void doSomething();
};

class alien;

class weapons;

class goodies;

class Star : public Actor
{
public:
	Star(StudentWorld* world);
	~Star();
	void doSomething();
};

#endif // _ACTOR_H_