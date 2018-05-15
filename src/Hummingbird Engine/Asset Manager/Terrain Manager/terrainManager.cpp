#include "terrainManager.h"

#include "../../Additions/Terrain/Terrain.h"
#include "../Model Manger/modelManager.h"

terrainManager* terrainManager::currentInstanceTerrainManager = nullptr;

#define DEBUGOUT 1

void terrainManager::privateLoadDefaultTerrains()
{
#if DEBUGOUT
DebugMsg::out("\nLoading Default Terrain\n");
#endif // DEBUGOUT
}

void terrainManager::privateLoadTerrain(std::string userNameOfTerrain, const char * fileNameOfTerrain, std::string userNameOfTexture, int size, int RepeatU, int RepeatV)
{
#if DEBUGOUT
	DebugMsg::out("Loading Terrain: %s", userNameOfTerrain.c_str());
#endif // DEBUGOUT
	if (mapOfUserNamesToPointers[userNameOfTerrain] == nullptr)
	{
		std::string completeDirectory = "Terrain/";
		mapOfUserNamesToPointers[userNameOfTerrain] = new Terrain(completeDirectory.append(fileNameOfTerrain).c_str(), userNameOfTexture,size,RepeatU,RepeatV);
	}
	else
	{
#if DEBUGOUT
DebugMsg::out("->Failed\n");
#endif // DEBUGOUT
		assert(false && "This name is already being used by another Terrain");
	}
#if DEBUGOUT
	DebugMsg::out("->Success\n");
#endif // DEBUGOUT
}
void terrainManager::privateUnloadSpecificTerrain(std::string userNameOfTerrain)
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Terrain: %s\n", userNameOfTerrain.c_str());
#endif // DEBUGOUT
	//first delete the news
	delete mapOfUserNamesToPointers[userNameOfTerrain];
	//then remove from the map
	mapOfUserNamesToPointers.erase(userNameOfTerrain);
}

void terrainManager::privateUnloadAllTerrains()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting All Terrain\n");
#endif // DEBUGOUT
	//delete all Terrain pointers individually
	for (std::map<std::string, Terrain*>::iterator it = mapOfUserNamesToPointers.begin(); it != mapOfUserNamesToPointers.end(); ++it)
	{
#if DEBUGOUT
		DebugMsg::out("Deleting Terrain: %s\n", it->first.c_str());
#endif // DEBUGOUT
		delete it->second;
	}
	//Then clear the map
	mapOfUserNamesToPointers.clear();
	//final delete manager
	delete currentInstanceTerrainManager;
	currentInstanceTerrainManager = nullptr;
}

Terrain * terrainManager::privateGetTerrainFromMap(std::string userNameOfTerrain)
{
	return mapOfUserNamesToPointers[userNameOfTerrain];
}

void terrainManager::privatePutTerrainInScene(std::string userNameOfTerrain)
{
	pCurrentTerrainUsed = mapOfUserNamesToPointers[userNameOfTerrain];
	pCurrentTerrainUsed->submitEntry();
}

void terrainManager::privateRemoveTerrainInScene(std::string userNameOfTerrain)
{
	pCurrentTerrainUsed = mapOfUserNamesToPointers[userNameOfTerrain];
	pCurrentTerrainUsed->submitExit();
	pCurrentTerrainUsed->sceneExit();

}

Terrain* terrainManager::privateGetCurrentTerrain()
{
	return pCurrentTerrainUsed;
}

terrainManager::~terrainManager()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Terrain Manager\n");
#endif // DEBUGOUT
}