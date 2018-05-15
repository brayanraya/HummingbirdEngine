#include "drawableRegistratonCommand.h"
#include "../Drawable/drawable.h"

drawableRegistratonCommand::~drawableRegistratonCommand()
{
}

drawableRegistratonCommand::drawableRegistratonCommand(drawable* up): drawablePointer(up)
{
}

void drawableRegistratonCommand::execute()
{
	drawablePointer->sceneRegistraion();
}
