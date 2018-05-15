#include "EnemtBulletFactoryWithRecycling.h"
#include "EnemtBullet.h"

EnemyBulletFactoryWithRecycling* EnemyBulletFactoryWithRecycling::ptrInstance = NULL;


void EnemyBulletFactoryWithRecycling::privCreateEnemtBullet(const Vect& pos, const Matrix& rot)
{
	EnemyBullet* b;
	std::list<EnemyBullet*>::iterator it = onScreen.end();
	if (recycledItems.size() < 2)
	{
		//DebugMsg::out("New EnemtBullet\n");
		b = new EnemyBullet();
		// Declares that this object should be returned here (rather than deleted) when destroyed
	}
	else
	{
		//DebugMsg::out("Recycled EnemtBullet\n");
		b = recycledItems.front();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->sceneEntry();
	}
	b->quickRemovePos = onScreen.insert(it, b);
	b->fromFactory(pos,rot);
}

void EnemyBulletFactoryWithRecycling::privRecycleEnemtBullet(EnemyBullet* b)
{
	onScreen.erase(b->quickRemovePos);
	recycledItems.push(b);

	//::out("Recycled Stack Size: %d\n", recycledItems.size());
	//::out("Recycled OnScreen Size: %d\n", onScreen.size());
}


void EnemyBulletFactoryWithRecycling::privTerminate()
{ 
	privreturnAllObjects();
							// forcefully delele all recycled gameobjects
	while (!onScreen.empty())
	{
		EnemyBullet* temp = onScreen.front();
		temp->sceneExit();
	}
	while (!recycledItems.empty())
	{
		delete recycledItems.front();
		recycledItems.pop();
	}

	//DebugMsg::out("Deleted Recycled items: %d\n", recycledItems.size());
	//DebugMsg::out("Deleting OnScreen items: %d\n", onScreen.size());
}

void EnemyBulletFactoryWithRecycling::privreturnAllObjects()
{
	while (!onScreen.empty())
	{
		onScreen.front()->sceneExit();
	}
}

// Why is this necessary?
EnemyBulletFactoryWithRecycling::~EnemyBulletFactoryWithRecycling()
{
	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}