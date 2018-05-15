#include "inputableDeregistratonCommand.h"

inputableDeregistratonCommand::inputableDeregistratonCommand(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType): inputablePointer(input), givenKey(inKey), givenType(inType)
{
}

void inputableDeregistratonCommand::execute()
{
	inputablePointer->sceneDeregistraion(givenKey,givenType);
}
