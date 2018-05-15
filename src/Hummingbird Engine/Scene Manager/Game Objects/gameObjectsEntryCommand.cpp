#include "gameObjectsEntryCommand.h"
#include "gameObjects.h"

gameObjectsEntryCommand::gameObjectsEntryCommand(gameObjects* inObject): myObject(inObject)
{
}
void gameObjectsEntryCommand::execute()
{
	myObject->connectToScene();
}
