#include "textureManager.h"

#include "../Model Manger/modelManager.h"

textureManager* textureManager::currentInstanceTextureManager = nullptr;
std::map<std::string, Texture*> textureManager::mapOfUserNamesToPointers;
std::string TextureFolder = "Textures/";

#define DEBUGOUT 1

void textureManager::privateLoadDefaultTextures()
{
#if DEBUGOUT
	DebugMsg::out("Loading Default Textures\n");
#endif // DEBUGOUT
}

void textureManager::privateLoadTexture(std::string userNameOfTexture, const char * fileNameOfTexture)
{
#if DEBUGOUT 
	DebugMsg::out("Loading Texture: %s", userNameOfTexture.c_str());
#endif // DEBUGOUT
	std::string completeDirectory(TextureFolder);
	if (mapOfUserNamesToPointers[userNameOfTexture] == nullptr)
	{
		mapOfUserNamesToPointers[userNameOfTexture] = new Texture(completeDirectory.append(fileNameOfTexture).c_str());
	}
	else
	{
#if DEBUGOUT
		DebugMsg::out("->Failed\n");
#endif // DEBUGOUT
		assert(false && "This name is already being used by another Texture");
	}
#if DEBUGOUT
	DebugMsg::out("->Success\n");
#endif // DEBUGOUT
}
void textureManager::privateUnloadSpecificTexture(std::string userNameOfTexture)
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Texture: %s\n", userNameOfTexture.c_str());
#endif // DEBUGOUT
	//first delete the news
	delete mapOfUserNamesToPointers[userNameOfTexture];
	//then remove from the map
	mapOfUserNamesToPointers.erase(userNameOfTexture);
}

void textureManager::privateUnloadAllTextures()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting All Textures\n");
#endif // DEBUGOUT
	//delete all Texture pointers individually
	for (std::map<std::string, Texture*>::iterator it = mapOfUserNamesToPointers.begin(); it != mapOfUserNamesToPointers.end(); ++it)
	{
#if DEBUGOUT
		DebugMsg::out("Deleting Texture: %s\n", it->first.c_str());
#endif // DEBUGOUT
		delete it->second;
	}
	//Then clear the map
	mapOfUserNamesToPointers.clear();
	//final delete manager
	delete currentInstanceTextureManager;
	currentInstanceTextureManager = nullptr;
}

Texture * textureManager::privateGetTextureFromMap(std::string userNameOfTexture)
{
	return mapOfUserNamesToPointers[userNameOfTexture];
}

textureManager::~textureManager()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Texture Manager\n");
#endif // DEBUGOUT
}