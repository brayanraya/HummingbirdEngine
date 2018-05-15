#include "drawableManager.h"
#include "../Drawable/drawable.h"
#include "../../../CollisionSystem/Tools/Visualizer.h"
drawableManager::~drawableManager()
{
}

void drawableManager::registerDrawable(drawable* draw)
{
	draw->myDeleteRef = drawableManagerList.insert(drawableManagerList.begin(), draw);
}

void drawableManager::deregisterDrawable(drawable* draw)
{
	drawableManagerList.erase(draw->myDeleteRef);
}

void drawableManager::processElements()
{
	for (drawableListRef it = drawableManagerList.begin(); it != drawableManagerList.end(); it++)
	{
		(*it)->draw();
	}

	Visualizer::renderAll();

	for (drawableListRef it = drawableManagerList.begin(); it != drawableManagerList.end(); it++)
	{
		(*it)->drawHUD();
	}
}
