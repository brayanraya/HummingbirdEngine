#include "updateableManager.h"
#include "../updateable/updateable.h"

updateableManager::~updateableManager()
{
}

void updateableManager::registerUpdateable(updateable* update)
{
	update->myDeleteRef = updateableManagerList.insert(updateableManagerList.begin(), update);
}

void updateableManager::deregisterUpdateable(updateable* update)
{
	updateableManagerList.erase(update->myDeleteRef);
}

void updateableManager::processElements()
{
	for (updateableListRef it = updateableManagerList.begin(); it != updateableManagerList.end(); it++)
	{
		(*it)->update();
	}
}
