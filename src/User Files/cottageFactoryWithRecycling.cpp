#include "cottageFactoryWithRecycling.h"
#include "cottage.h"

cottageFactoryWithRecycling* cottageFactoryWithRecycling::ptrInstance = NULL;


void cottageFactoryWithRecycling::privCreatecottage(const Vect& inVec)
{
	cottage* b;
	std::list<cottage*>::iterator it = onScreen.end();
	if (recycledItems.size() < 2)
	{
		 DebugMsg::out("New cottage\n");
		b = new cottage();
		// Declares that this object should be returned here (rather than deleted) when destroyed
	}
	else
	{
		DebugMsg::out("Recycled cottage\n");
		b = recycledItems.front();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->sceneEntry();
	}
	b->quickRemovePos = onScreen.insert(it, b);
	b->fromFactory(inVec);
}

void cottageFactoryWithRecycling::privRecyclecottage(cottage* b)
{
	onScreen.erase(b->quickRemovePos);
	recycledItems.push(b);
	// For illustration purposes
	DebugMsg::out("Recycled Stack Size: %d\n", recycledItems.size());
	DebugMsg::out("Recycled OnScreen Size: %d\n", onScreen.size());

}

void cottageFactoryWithRecycling::privSetAllDarkness(const Vect& inVec)
{
	for (std::list<cottage*>::iterator it = onScreen.begin(); it != onScreen.end(); ++it)
	{
		(*it)->darkness(inVec);
	}
}

void cottageFactoryWithRecycling::privSetAllLightness()
{
	for (std::list<cottage*>::iterator it = onScreen.begin(); it != onScreen.end(); ++it)
	{
		(*it)->lightness();
	}
}

void cottageFactoryWithRecycling::privreturnAllObjects()
{
	while (!onScreen.empty())
	{
		onScreen.front()->sceneExit();
		onScreen.pop_front();
	}
}

void cottageFactoryWithRecycling::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}


// Why is this necessary?
cottageFactoryWithRecycling::~cottageFactoryWithRecycling()
{
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