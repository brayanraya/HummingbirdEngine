#include "updateableRegistratonCommand.h"
#include "../updateable/updateable.h"

updateableRegistratonCommand::updateableRegistratonCommand(updateable* up): updateablePointer(up)
{
}

void updateableRegistratonCommand::execute()
{
	updateablePointer->sceneRegistraion();
}
