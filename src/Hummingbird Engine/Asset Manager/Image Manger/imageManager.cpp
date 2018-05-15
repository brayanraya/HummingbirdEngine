#include "../Texture Manager/textureManager.h"
#include "imageManager.h"

ImageManager* ImageManager::currentInstanceImageManager = nullptr;
std::map<std::string, Image*> ImageManager::mapOfUserNamesToPointers;

#define DEBUGOUT 1

void ImageManager::privateLoadDefaultImages()
{
#if DEBUGOUT
	DebugMsg::out("\nLoading Default Images\n");
#endif
}

void ImageManager::privateLoadImage(std::string userNameOfImage, std::string userTextureName, float startX, float startY, float width, float height)
{
#if DEBUGOUT
	DebugMsg::out("Loading Image: %s", userNameOfImage.c_str());
#endif
	if (mapOfUserNamesToPointers[userNameOfImage] == nullptr)
	{
		if (width == 0 || height == 0)
		{
			float textureWidth = (float)textureManager::getTextureFromMap(userTextureName)->getWidth();
			float textureHeight = (float)textureManager::getTextureFromMap(userTextureName)->getHeight();
			mapOfUserNamesToPointers[userNameOfImage] = new Image(textureManager::getTextureFromMap(userTextureName), new Rect(startX, startY, textureWidth, textureHeight));

		}
		else
		{
			mapOfUserNamesToPointers[userNameOfImage] = new Image(textureManager::getTextureFromMap(userTextureName), new Rect(startX, startY, width, height));
		}
	}
	else
	{
#if DEBUGOUT
		DebugMsg::out("->Failed\n");
#endif

		assert(false && "This name is already being used by another Image");
	}
#if DEBUGOUT
	DebugMsg::out("->Success\n");
#endif
}

void ImageManager::privateUnloadSpecificImage(std::string userNameOfImage)
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Image: %s\n", userNameOfImage.c_str());
#endif
	//first delete the news
	delete mapOfUserNamesToPointers[userNameOfImage];
	//then remove from the map
	mapOfUserNamesToPointers.erase(userNameOfImage);
}

void ImageManager::privateUnloadAllImages()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting All Images\n");
#endif
	//delete all Image pointers individually
	for (std::map<std::string, Image*>::iterator it = mapOfUserNamesToPointers.begin(); it != mapOfUserNamesToPointers.end(); ++it)
	{
#if DEBUGOUT
		DebugMsg::out("Deleting Image: %s\n", it->first.c_str());
#endif
		delete it->second;
	}
	//Then clear the map
	mapOfUserNamesToPointers.clear();
	//final delete manager
	delete currentInstanceImageManager;
	currentInstanceImageManager = nullptr;
}

Image * ImageManager::privateGetImageFromMap(std::string userNameOfImage)
{
	return mapOfUserNamesToPointers[userNameOfImage];
}

ImageManager::~ImageManager()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Image Manager\n");
#endif
}