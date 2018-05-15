#include "gameObjectsManager.h"
#include "gameObjects.h"
#include "../../Main Game/hummingbirdEngine.h"

gameObjectsManager::~gameObjectsManager()
{
}

void gameObjectsManager::registerGameObjects(gameObjects* inObject, SCENE_ID type)
{
	if (type == SCENE_ID::ENTER)
	{
		inObject->myDeleteEnterRef = gameObjectsEnterList.insert(gameObjectsEnterList.begin(), inObject);
	}
	else
	{
		inObject->myDeleteExitRef = gameObjectsExitList.insert(gameObjectsExitList.begin(), inObject);
	}
}

void gameObjectsManager::deregisterGameObjects(gameObjects* inObject, SCENE_ID type)
{
	if (type == SCENE_ID::ENTER)
	{
		gameObjectsEnterList.erase(inObject->myDeleteEnterRef);
	}
	else
	{
		gameObjectsExitList.erase(inObject->myDeleteExitRef);
	}
}

void gameObjectsManager::processElements()
{
	std::list<gameObjects*>::iterator it = gameObjectsEnterList.begin();
	std::list<gameObjects*>::iterator tempIt(it);
	while (it != gameObjectsEnterList.end())
	{
		(*it)->sceneEntry();
		//std::list<gameObjects*>::iterator tempIt(it);
		tempIt++;
		deregisterGameObjects(*it, SCENE_ID::ENTER);
		it = tempIt;
	}
	it = gameObjectsExitList.begin();
	while (it != gameObjectsExitList.end())
	{
		(*it)->sceneExit();
		tempIt = it;
		tempIt++;
		deregisterGameObjects(*it, SCENE_ID::EXIT);
		it = tempIt;
	}
}
