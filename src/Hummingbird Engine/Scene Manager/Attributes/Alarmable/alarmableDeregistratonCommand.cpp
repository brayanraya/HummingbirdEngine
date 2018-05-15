#include "alarmableDeregistratonCommand.h"
#include "../alarmable/alarmable.h"

alarmableDeregistratonCommand::alarmableDeregistratonCommand()
{
}


alarmableDeregistratonCommand::~alarmableDeregistratonCommand()
{
}

alarmableDeregistratonCommand::alarmableDeregistratonCommand(alarmable* up): alarmablePointer(up) 
{
}

void alarmableDeregistratonCommand::execute()
{
	alarmablePointer->sceneDeregistraion(alarmId);
}
