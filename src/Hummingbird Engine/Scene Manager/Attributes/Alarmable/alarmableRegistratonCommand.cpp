#include "alarmableRegistratonCommand.h"
#include "../alarmable/alarmable.h"

alarmableRegistratonCommand::alarmableRegistratonCommand()
{
}


alarmableRegistratonCommand::~alarmableRegistratonCommand()
{
}

alarmableRegistratonCommand::alarmableRegistratonCommand(alarmable* up): alarmablePointer(up) 
{
}

void alarmableRegistratonCommand::execute()
{
	alarmablePointer->sceneRegistraion(alarmTime, alarmId);
}
