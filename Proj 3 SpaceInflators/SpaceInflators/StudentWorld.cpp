#include "StudentWorld.h"
#include "actor.h"
using namespace std;

GameWorld* createStudentWorld()
{
    return new StudentWorld();
}

StudentWorld::StudentWorld()
{
}

StudentWorld::~StudentWorld()
{
	for(int i = 0; i != m_actors.size(); i++)
	{
		delete m_actors[i];
	}
	delete player;
}

void StudentWorld::addAliensOrStars()
{
	int p3 = rand() % 100;
	if(p3 < 33)
		m_actors.push_back(new Star(this));
}

void StudentWorld::removeDeadGameObjects()
{
	for(int i = 0; i < m_actors.size(); i++)
	{
		if(!m_actors[i]->isAlive())
		{
			m_actors[i]->setVisible(false);
			delete m_actors[i];
		}
	}
}