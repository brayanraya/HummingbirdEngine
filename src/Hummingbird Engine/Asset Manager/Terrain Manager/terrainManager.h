#ifndef _terrainManager
#define _terrainManager

#include "AzulCore.h"
#include <map>

class Terrain;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for Terrains loaded from file. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class terrainManager // singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	terrainManager() = default;
	~terrainManager();
	terrainManager(const terrainManager&) = delete;
	terrainManager& operator=(const terrainManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a terrainManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static terrainManager& Instance()
	{
		if (!currentInstanceTerrainManager)
			currentInstanceTerrainManager = new terrainManager;
		return *currentInstanceTerrainManager;
	};


	//------------------------------------
	//private Functions
	//------------------------------------
	
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Terrains are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void privateLoadDefaultTerrains();

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided Terrains to the map and allows that Terrain to be accesssed by they key.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTerrain">	The user name of Terrain. </param>
	/// <param name="fileNameOfTerrain">	The file name of Terrain. </param>
	///-------------------------------------------------------------------------------------------------
	void privateLoadTerrain(std::string userNameOfTerrain, const char * fileNameOfTerrain, std::string userNameOfTexture, int size, int RepeatU, int RepeatV);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Terrains from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void privateUnloadAllTerrains();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Terrain from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTerrain">	The user name of Terrain. </param>
	///-------------------------------------------------------------------------------------------------
	void privateUnloadSpecificTerrain(std::string userNameOfTerrain);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Terrain pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTerrain">	The user name of Terrain. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a Terrain. </returns>
	///-------------------------------------------------------------------------------------------------
	Terrain* privateGetTerrainFromMap(std::string userNameOfTerrain);

	void privatePutTerrainInScene(std::string userNameOfTerrain);

	void privateRemoveTerrainInScene(std::string userNameOfTerrain);

	Terrain* privateGetCurrentTerrain();

	//------------------------------------
	//private variables
	//------------------------------------
	static terrainManager* currentInstanceTerrainManager;
	std::map<std::string, Terrain *> mapOfUserNamesToPointers;
	Terrain* pCurrentTerrainUsed;

public:
	//------------------------------------
	//Public API
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Terrains are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void loadDefaultTerrains() { Instance().privateLoadDefaultTerrains(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided Terrains to the map and allows that Terrain to be accesssed by they key The
	/// 	userNameOfTerrain is the name the user will use when refering to the Terrain The
	/// 	fileNameOfTerrain is the name of the Terrain as it appears in the assets/Terrain folder
	/// 	w/o extension.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTerrain">	The user name of Terrain. </param>
	/// <param name="fileNameOfTerrain">	The file name of Terrain. </param>
	///-------------------------------------------------------------------------------------------------
	static void loadTerrain(std::string userNameOfTerrain, const char * fileNameOfTerrain, std::string userNameOfTexture, int size = 100, int RepeatU = 1, int RepeatV = 1) { Instance().privateLoadTerrain(userNameOfTerrain, fileNameOfTerrain, userNameOfTexture, size,RepeatU,RepeatV); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Terrain from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTerrain">	The user name of Terrain. </param>
	///-------------------------------------------------------------------------------------------------
	static void unloadSpecificTerrain(std::string userNameOfTerrain) { Instance().privateUnloadSpecificTerrain(userNameOfTerrain); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Terrains from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void unloadAllTerrains() { Instance().privateUnloadAllTerrains(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Terrain pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTerrain">	The user name of Terrain. </param>
	///
	/// <returns>	Null if it fails, else the Terrain from map. </returns>
	///-------------------------------------------------------------------------------------------------
	static Terrain* getTerrainFromMap(std::string userNameOfTerrain) { return Instance().privateGetTerrainFromMap(userNameOfTerrain); };

	static void PutTerrainInScene(std::string userNameOfTerrain) { return Instance().privatePutTerrainInScene(userNameOfTerrain); };

	static void RemoveTerrainInScene(std::string userNameOfTerrain) { return Instance().privateRemoveTerrainInScene(userNameOfTerrain); };


	static Terrain* getCurrentTerrain() { return Instance().privateGetCurrentTerrain(); };

};

#endif // !_terrainManager