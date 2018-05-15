#include "inputableRegistratonCommand.h"

inputableRegistratonCommand::inputableRegistratonCommand()
{
}


inputableRegistratonCommand::~inputableRegistratonCommand()
{
}

inputableRegistratonCommand::inputableRegistratonCommand(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType) : inputablePointer(input), givenKey(inKey), givenType(inType)
{
}

void inputableRegistratonCommand::execute()
{
	inputablePointer->sceneRegistraion(givenKey,givenType);
}
