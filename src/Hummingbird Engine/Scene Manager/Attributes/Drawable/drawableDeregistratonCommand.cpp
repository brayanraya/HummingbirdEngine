#include "drawableDeregistratonCommand.h"
#include "../Drawable/drawable.h"

drawableDeregistratonCommand::drawableDeregistratonCommand()
{
}


drawableDeregistratonCommand::~drawableDeregistratonCommand()
{
}

drawableDeregistratonCommand::drawableDeregistratonCommand(drawable* up): drawablePointer(up)
{
}

void drawableDeregistratonCommand::execute()
{
	drawablePointer->sceneDeregistraion();
}
