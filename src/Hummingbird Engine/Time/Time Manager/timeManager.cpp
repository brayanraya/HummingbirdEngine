#include "timeManager.h"

timeManager* timeManager::currentInstanceTimeManager = nullptr;

timeManager::~timeManager()
{
}

void timeManager::privProcessTime(float inTime)
{
	previousTime	= currentTime;
	//currentTime		= inTime;
	currentTime = pause.getTimeInSeconds(inTime);
	frameNumber	= currentTime - previousTime;
	secondTimeHolder += frameNumber;
	currentFPS++;
	if (secondTimeHolder > 1.0f)
	{
		secondTimeHolder = 0;
		if (currentFPS != averageFPS)
		{
			averageFPS = currentFPS;
		}
		currentFPS = 0;
	}
	//return frameTime;
}
