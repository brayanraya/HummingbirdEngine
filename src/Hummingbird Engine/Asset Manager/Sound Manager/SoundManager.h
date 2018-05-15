#ifndef _SoundManager
#define _SoundManager

#include "AzulCore.h"
#include <map>

namespace irrklang
{
	class ISound;
	class ISoundEngine;
	class ISoundSource;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for Sounds loaded from file. </summary>
///
/// <remarks>	Braya, 5/25/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class SoundManager // singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	SoundManager();
	void privateTerminate();
	~SoundManager();
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a SoundManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static SoundManager& Instance()
	{
		if (!currentInstanceSoundManager)
			currentInstanceSoundManager = new SoundManager;
		return *currentInstanceSoundManager;
	};

	//------------------------------------
	//private Functions
	//------------------------------------
	void privateLoadSound(std::string userNameOfSound, std::string fileLocation);
	void privatePlaySound(std::string userNameOfSound, bool looped);
	void privateStopSound(std::string userNameOfSound);
	void privateUnloadAllSounds();

	irrklang::ISound* privateGetSound(std::string userNameOfSound);



	//------------------------------------
	//private variables
	//------------------------------------
	static SoundManager* currentInstanceSoundManager;
	static irrklang::ISoundEngine* pSoundEngine;
	static std::map<std::string, irrklang::ISoundSource*> mapOfUserNamesToPointers;
	static std::map<std::string, irrklang::ISound*> mapOfCreatedSounds;


public:
	static void loadSound(std::string userNameOfSound, std::string fileLocation) { Instance().privateLoadSound(userNameOfSound, fileLocation); };
	static void playSound(std::string userNameOfSound, bool looped = false) {  Instance().privatePlaySound(userNameOfSound,looped);};
	static void stopSound(std::string userNameOfSound) { Instance().privateStopSound(userNameOfSound); };
	static void unloadAllSounds() { Instance().privateUnloadAllSounds(); };
	static irrklang::ISound* getSound(std::string userNameOfSound) { return Instance().privateGetSound(userNameOfSound);}
};

#endif

