#include "singleKeyEventManager.h"

singleKeyEventManager::singleKeyEventManager(AZUL_KEY inKey): myKey(inKey)
{
	lastStateOfKey = false;
	currentlyDown = false;
}

singleKeyEventManager::~singleKeyEventManager()
{
}

void singleKeyEventManager::registerinputable(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType)
{
	inputable::KeyEvent temp(inKey, inType);
	if (inType == inputable::INPUT_TYPE::PRESS)
	{
		(input->inputableMapOfKeys[temp])->pressListDeleteRef= keyPressCol.insert(keyPressCol.begin(), input);
	}
	else
	{
		(input->inputableMapOfKeys[temp])->releaseListDeleteRef = keyReleasedCol.insert(keyReleasedCol.begin(), input);
	}
}

void singleKeyEventManager::deregisterinputable(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType)
{
	inputable::KeyEvent temp(inKey, inType);
	if (inType == inputable::INPUT_TYPE::PRESS)
	{
		keyPressCol.erase((input->inputableMapOfKeys[temp])->pressListDeleteRef);
	}
	else
	{
		keyReleasedCol.erase((input->inputableMapOfKeys[temp])->releaseListDeleteRef);
	}
}

void singleKeyEventManager::processElements()
{
	if (lastStateOfKey != Keyboard::GetKeyState(myKey) && !currentlyDown)
	{
		for (inputable::keyListRef it = keyPressCol.begin(); it != keyPressCol.end(); ++it)
		{
			(*it)->keyPress(myKey);
		}
		lastStateOfKey = Keyboard::GetKeyState(myKey);
		currentlyDown = true;
	}
	else if (lastStateOfKey != Keyboard::GetKeyState(myKey) && currentlyDown)
	{
		for (inputable::keyListRef it = keyReleasedCol.begin(); it != keyReleasedCol.end(); ++it)
		{
			(*it)->keyRelease(myKey);
		}
		lastStateOfKey = Keyboard::GetKeyState(myKey);
		currentlyDown = false;
	}
	else
	{
		lastStateOfKey = Keyboard::GetKeyState(myKey);
	}
}
