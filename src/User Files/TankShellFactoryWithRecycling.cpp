#include "TankShellFactoryWithRecycling.h"
#include "TankShell.h"

TankShellFactoryWithRecycling* TankShellFactoryWithRecycling::ptrInstance = NULL;


void TankShellFactoryWithRecycling::privCreateTankShell(const Vect& pos, const Matrix& rot)
{
	TankShell* b;
	std::list<TankShell*>::iterator it = onScreen.end();
	if (recycledItems.size() < 2)
	{
		//DebugMsg::out("New TankShell\n");
		b = new TankShell();
		// Declares that this object should be returned here (rather than deleted) when destroyed
	}
	else
	{
		//DebugMsg::out("Recycled TankShell\n");
		b = recycledItems.front();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->sceneEntry();
	}
	b->quickRemovePos = onScreen.insert(it, b);
	b->fromFactory(pos,rot);
}

void TankShellFactoryWithRecycling::privRecycleTankShell(TankShell* b)
{
	onScreen.erase(b->quickRemovePos);
	recycledItems.push(b);

	//::out("Recycled Stack Size: %d\n", recycledItems.size());
	//::out("Recycled OnScreen Size: %d\n", onScreen.size());

}


void TankShellFactoryWithRecycling::privTerminate()
{ 
	returnAllObjects();

	// forcefully delele all recycled gameobjects
	while (!onScreen.empty())
	{
		TankShell* temp = onScreen.front();
		temp->sceneExit();
	}
	while (!recycledItems.empty())
	{
		delete recycledItems.front();
		recycledItems.pop();
	}
}

void TankShellFactoryWithRecycling::privreturnAllObjects()
{
	while (!onScreen.empty())
	{
		onScreen.front()->sceneExit();
	}
}

// Why is this necessary?
TankShellFactoryWithRecycling::~TankShellFactoryWithRecycling()
{

	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}