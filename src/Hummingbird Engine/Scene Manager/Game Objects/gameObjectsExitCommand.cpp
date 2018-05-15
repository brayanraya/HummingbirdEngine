#include "gameObjectsExitCommand.h"
#include "gameObjects.h"
//gameObjectsExitCommand::gameObjectsExitCommand()
//{
//}

gameObjectsExitCommand::gameObjectsExitCommand(gameObjects* inObject) : myObject(inObject)
{
}

//gameObjectsExitCommand::~gameObjectsExitCommand()
//{
//}

void gameObjectsExitCommand::execute()
{
	myObject->disconnectToScene();
}
