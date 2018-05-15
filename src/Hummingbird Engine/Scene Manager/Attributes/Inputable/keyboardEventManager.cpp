#include "keyboardEventManager.h"


keyboardEventManager::~keyboardEventManager()
{
	for (inputable::keyboardMap::iterator it = keyboardEventManagerList.begin(); it != keyboardEventManagerList.end(); ++it)
	{
		delete (it->second);
	}
}

void keyboardEventManager::registerinputable(inputable * input, std::pair<AZUL_KEY, inputable::INPUT_TYPE> inPair)
{
	if (keyboardEventManagerList[inPair.first] == nullptr)
	{
		keyboardEventManagerList[inPair.first] = new singleKeyEventManager(inPair.first);
	}

	if (inPair.second == inputable::INPUT_TYPE::PRESS)
	{
		(input->inputableMapOfKeys[inPair])->mapDeleteRef = keyboardEventManagerList.insert(keyboardEventManagerList.begin(), std::pair<AZUL_KEY, singleKeyEventManager*>(inPair.first, keyboardEventManagerList[inPair.first]));
	}
	else
	{
		(input->inputableMapOfKeys[inPair])->mapDeleteRef = keyboardEventManagerList.insert(keyboardEventManagerList.begin(), std::pair<AZUL_KEY, singleKeyEventManager*>(inPair.first, keyboardEventManagerList[inPair.first]));
	}

	keyboardEventManagerList[inPair.first]->registerinputable(input, inPair.first, inPair.second);
}

void keyboardEventManager::deregisterinputable(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType)
{
	keyboardEventManagerList[inKey]->deregisterinputable(input, inKey, inType);
	bool isPressEmpty(keyboardEventManagerList[inKey]->keyPressCol.empty()); //checks if press list is empty
	bool isReleaseEmpty(keyboardEventManagerList[inKey]->keyReleasedCol.empty()); // checks if release list is empty
	if (isPressEmpty && isReleaseEmpty)
	{
		inputable::KeyEvent temp(inKey, inType);
		if (inType == inputable::INPUT_TYPE::PRESS)
		{
			keyboardEventManagerList.erase(((input->inputableMapOfKeys[temp]))->mapDeleteRef);
		}
		else
		{
			keyboardEventManagerList.erase(((input->inputableMapOfKeys[temp]))->mapDeleteRef);
		} 
	}
	
}

void keyboardEventManager::processElements()
{
	inputable::keyboardMapRef it = keyboardEventManagerList.begin();

	while (it != keyboardEventManagerList.end())
	{

		(*it).second->processElements();
		inputable::keyboardMapRef tempIt(it);
		tempIt++;
		it = tempIt;
	}
}
