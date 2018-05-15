#include "updateableDeregistratonCommand.h"
#include "../updateable/updateable.h"
updateableDeregistratonCommand::updateableDeregistratonCommand(updateable* up): updateablePointer(up)
{
}

void updateableDeregistratonCommand::execute()
{
	updateablePointer->sceneDeregistraion();
}
