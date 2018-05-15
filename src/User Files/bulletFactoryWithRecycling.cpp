#include "bulletFactoryWithRecycling.h"
#include "bullet.h"

bulletFactoryWithRecycling* bulletFactoryWithRecycling::ptrInstance = NULL;


void bulletFactoryWithRecycling::privCreatebullet(const Vect& pos, const Matrix& rot)
{
	bullet* b;
	std::list<bullet*>::iterator it = onScreen.end();
	if (recycledItems.size() < 2)
	{
		//DebugMsg::out("New bullet\n");
		b = new bullet();
		// Declares that this object should be returned here (rather than deleted) when destroyed
	}
	else
	{
		//DebugMsg::out("Recycled bullet\n");
		b = recycledItems.front();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->sceneEntry();
	}
	b->quickRemovePos = onScreen.insert(it, b);
	b->fromFactory(pos,rot);
}

void bulletFactoryWithRecycling::privRecyclebullet(bullet* b)
{
	onScreen.erase(b->quickRemovePos);
	recycledItems.push(b);

	//::out("Recycled Stack Size: %d\n", recycledItems.size());
	//::out("Recycled OnScreen Size: %d\n", onScreen.size());

}


void bulletFactoryWithRecycling::privTerminate()
{ 
	returnAllObjects();

	// forcefully delele all recycled gameobjects
	while (!onScreen.empty())
	{
		bullet* temp = onScreen.front();
		temp->sceneExit();
	}
	while (!recycledItems.empty())
	{
		delete recycledItems.front();
		recycledItems.pop();
	}
}

void bulletFactoryWithRecycling::privreturnAllObjects()
{
	while (!onScreen.empty())
	{
		onScreen.front()->sceneExit();
	}
}

// Why is this necessary?
bulletFactoryWithRecycling::~bulletFactoryWithRecycling()
{

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}