#include "toySoldierFactoryWithRecycling.h"
#include "EnemySoldier.h"

toySoldierFactoryWithRecycling* toySoldierFactoryWithRecycling::ptrInstance = NULL;


void toySoldierFactoryWithRecycling::privCreatetoySoldier()
{
	EnemySoldier* b;
	std::list<EnemySoldier*>::iterator it = onScreen.end();
	if (recycledItems.size() == 0)
	{
		DebugMsg::out("New toySoldier\n");
		b = new EnemySoldier();
		// Declares that this object should be returned here (rather than deleted) when destroyed
	}
	else
	{
		DebugMsg::out("Recycled toySoldier\n");
		b = recycledItems.front();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->sceneEntry();
	}
	b->quickRemovePos = onScreen.insert(it, b);
	b->fromFactory();
}

void toySoldierFactoryWithRecycling::privRecycletoySoldier(EnemySoldier* b)
{
	onScreen.erase(b->quickRemovePos);
	recycledItems.push(b);
	// For illustration purposes
	DebugMsg::out("Recycled Stack Size: %d\n", recycledItems.size());
	DebugMsg::out("Recycled OnScreen Size: %d\n", onScreen.size());

}

void toySoldierFactoryWithRecycling::privreturnAllObjects()
{
	while (!onScreen.empty())
	{
		onScreen.front()->sceneExit();
		onScreen.pop_front();
	}
}

void toySoldierFactoryWithRecycling::privAllFace(const Vect & playerPos)
{
	for (std::list<EnemySoldier*>::iterator it = onScreen.begin(); it != onScreen.end(); ++it)
	{
		(*it)->FacePlayer(playerPos);
	}
}

void toySoldierFactoryWithRecycling::privTerminate()
{
	privreturnAllObjects();
	DebugMsg::out("Deleting Recycled items: %d\n", recycledItems.size());
	DebugMsg::out("Deleting OnScreen items: %d\n", onScreen.size());
	// forcefully delele all recycled gameobjects
	while (!recycledItems.empty())
	{
		delete recycledItems.front();
		recycledItems.pop();
	}
	DebugMsg::out("Deleted Recycled items: %d\n", recycledItems.size());
	DebugMsg::out("Deleting OnScreen items: %d\n", onScreen.size());
}


// Why is this necessary?
toySoldierFactoryWithRecycling::~toySoldierFactoryWithRecycling()
{
	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}