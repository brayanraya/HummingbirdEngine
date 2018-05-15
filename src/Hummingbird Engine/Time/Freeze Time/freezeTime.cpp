#include "freezeTime.h"
#include "../../Main Game/hummingbirdEngine.h"


freezeTime::freezeTime()
{
}


freezeTime::~freezeTime()
{
}

float freezeTime::getTimeInSeconds(float inTime)
{
	float activeGameTime = inTime - totalFrozenTime;

	if (HackedKeyRelease(FREEZE_KEY) || freeze_mode_active)
	{
		DebugMsg::out("Freeze Frame at %f\n", activeGameTime);
		totalFrozenTime = WaitAndReturnFrozenTime(activeGameTime);
	}

	return activeGameTime;
}

float freezeTime::WaitAndReturnFrozenTime(float inTime)
{
	freeze_mode_active = true;
	bool single_Frame = false;

	while (freeze_mode_active && !single_Frame)
	{
		if (HackedKeyRelease(FREEZE_KEY))
		{
			freeze_mode_active = false;
			single_Frame = false;
		}
		if (HackedKeyRelease(SINGLE_FRAME_KEY))
		{
			single_Frame = true;
		}
		if (HackedKeyRelease(SINGLE_FRAME_KEY))
		{
			single_Frame = true;
		}
		glfwPollEvents();
	}
	return hummingbirdEngine::getSystemTime() - inTime;
}

bool freezeTime::HackedKeyRelease(AZUL_KEY inKey)
{
	if (Keyboard::GetKeyState(inKey))
	{
		while (Keyboard::GetKeyState(inKey))
		{
			glfwWaitEvents();
		}
		return true;
	}
	else
	{
		return false;
	}
}
