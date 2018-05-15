#include "sceneRegistrationBroker.h"

#include "../Attributes/Command/commandBase.h"

sceneRegistrationBroker::~sceneRegistrationBroker()
{
}

void sceneRegistrationBroker::addCommand(commandBase * add)
{
	commandManagerList.insert(commandManagerList.end(),add);
}
void sceneRegistrationBroker::executeCommands()
{
	for (std::list<commandBase*>::const_iterator it = commandManagerList.begin(); it != commandManagerList.end(); it++)
	{
		(*it)->execute();
	}
	commandManagerList.clear();
}
