#include "SoundManager.h"

#include "irrKlang.h"

irrklang::ISoundEngine* SoundManager::pSoundEngine = nullptr;
SoundManager* SoundManager::currentInstanceSoundManager = nullptr;
std::map<std::string, irrklang::ISoundSource*> SoundManager::mapOfUserNamesToPointers;
std::map<std::string, irrklang::ISound*> SoundManager::mapOfCreatedSounds;

#define DEBUGOUT 1

SoundManager::SoundManager()
{
#if DEBUGOUT
	DebugMsg::out("\nCreating Sound Manager\n");
#endif // DEBUGOUT
	pSoundEngine = irrklang::createIrrKlangDevice();
}


void SoundManager::privateTerminate()
{
	delete currentInstanceSoundManager;
}

SoundManager::~SoundManager()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Sound Manager\n");
#endif // DEBUGOUT
}

void SoundManager::privateLoadSound(std::string userNameOfSound, std::string fileLocation)
{
#if DEBUGOUT
	DebugMsg::out("Loading Sound: %s", userNameOfSound.c_str());
#endif //DEBUGOUT
	if (mapOfUserNamesToPointers[userNameOfSound] == nullptr)
	{
		std::string musicFolder = "Music/";
		mapOfUserNamesToPointers[userNameOfSound] = pSoundEngine->addSoundSourceFromFile(musicFolder.append(fileLocation).c_str());
	}
	else
	{
		#if DEBUGOUT 
		DebugMsg::out("->Failed\n");
		#endif //!DEBUGOUT
		assert(false && "This name is already being used by another Sound");
	}
#if DEBUGOUT 
	DebugMsg::out("->Sucess\n");
#endif //!DEBUGOUT
}

void SoundManager::privatePlaySound(std::string userNameOfSound, bool looped)
{
	if (mapOfUserNamesToPointers[userNameOfSound] != nullptr)
	{
		if (!looped)
		{
			pSoundEngine->play2D(mapOfUserNamesToPointers[userNameOfSound]);
		}
		else if (mapOfCreatedSounds[userNameOfSound] == nullptr)
		{
			mapOfCreatedSounds[userNameOfSound] = pSoundEngine->play2D(mapOfUserNamesToPointers[userNameOfSound],true,true);
			mapOfCreatedSounds[userNameOfSound]->setIsPaused(false);
		}
	}
}


void SoundManager::privateStopSound(std::string userNameOfSound)
{
		if (mapOfCreatedSounds[userNameOfSound] != nullptr)
		{
			mapOfCreatedSounds[userNameOfSound]->stop();
			mapOfCreatedSounds[userNameOfSound]->drop();
			mapOfCreatedSounds[userNameOfSound] = nullptr;
		}
}

void SoundManager::privateUnloadAllSounds()
{	
#if DEBUGOUT 
	DebugMsg::out("\nStopping All Sounds\n");
#endif //!DEBUGOUT
	pSoundEngine->stopAllSounds();
#if DEBUGOUT 
	DebugMsg::out("Removing All Sounds\n");
#endif //!DEBUGOUT
	pSoundEngine->removeAllSoundSources();
#if DEBUGOUT 
	DebugMsg::out("Terminating Sound Engine\n");
#endif //!DEBUGOUT
	pSoundEngine->drop();	

	//Then clear the map
#if DEBUGOUT 
	DebugMsg::out("Clearing Maps\n");
#endif //!DEBUGOUT
	mapOfUserNamesToPointers.clear();
	mapOfCreatedSounds.clear();

	//final delete manager
#if DEBUGOUT 
	DebugMsg::out("Deleting Instance\n");
#endif //!DEBUGOUT
	delete currentInstanceSoundManager;
	currentInstanceSoundManager = nullptr;
}

irrklang::ISound* SoundManager::privateGetSound(std::string userNameOfSound)
{
	if (mapOfUserNamesToPointers[userNameOfSound] != nullptr)
	{
		return pSoundEngine->play2D(mapOfUserNamesToPointers[userNameOfSound]);
	}
	else
	{
		assert(false && "Sound Not in Map");
		return nullptr;
	}
}
