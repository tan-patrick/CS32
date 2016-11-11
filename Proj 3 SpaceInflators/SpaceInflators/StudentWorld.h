#ifndef _STUDENTWORLD_H_
#define _STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <vector>
#include <algorithm>
using namespace std;
#include "actor.h"

class Actor;
class Ship;

class StudentWorld : public GameWorld
{
public:
	StudentWorld();
	~StudentWorld();
	void addAliensOrStars();
	void removeDeadGameObjects();
	virtual void init()
	{
		player = new PlayerShip(this);
	}

	virtual int move()
    {
		addAliensOrStars();
		for(int i = 0; i < m_actors.size(); i++)
		{
			if (m_actors[i]->isAlive())
				m_actors[i]->doSomething();
		}
		if(player->isAlive())
			player->doSomething();
		
		removeDeadGameObjects();
		
		if (!player->isAlive())
			return GWSTATUS_PLAYER_DIED;
		return GWSTATUS_CONTINUE_GAME;
    }

	virtual void cleanUp()
    {
		for(int i = 0; i < m_actors.size(); i++)
		{
			delete m_actors[i];
		}
    }

private:
	int numActors;
	vector<Actor*> m_actors;
	Ship* player;
};

#endif // _GAMEWORLD_H_