#ifndef _ImageManager
#define _ImageManager

#include "AzulCore.h"
#include "../Texture Manager/textureManager.h"
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for Images loaded from file. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ImageManager //singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	ImageManager() = default;
	~ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a ImageManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static ImageManager& Instance()
	{
		if (!currentInstanceImageManager)
			currentInstanceImageManager = new ImageManager;
		return *currentInstanceImageManager;
	};

	//------------------------------------
	//private Functions
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Images are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateLoadDefaultImages();


	void privateLoadImage(std::string userNameOfImage, std::string userTextureName, float width, float hight, float centerX, float centerY);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Images from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateUnloadAllImages();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Image from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfImage">	The user name of Image. </param>
	///-------------------------------------------------------------------------------------------------
	void privateUnloadSpecificImage(std::string userNameOfImage);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Image pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfImage">	The user name of Image. </param>
	///
	/// <returns>	Null if it fails, else a pointer to an Image. </returns>
	///-------------------------------------------------------------------------------------------------
	Image* privateGetImageFromMap(std::string userNameOfImage);


	//------------------------------------
	//private variables
	//------------------------------------
	static ImageManager* currentInstanceImageManager;
	static std::map<std::string, Image *> mapOfUserNamesToPointers;

public:
	//------------------------------------
	//Public API
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Images are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void loadDefaultImages() { Instance().privateLoadDefaultImages(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided Images to the map and allows that Image to be accesssed by they key The
	/// 	userNameOfImage is the name the user will use when refering to the Image The
	/// 	fileNameOfImage is the name of the Image as it appears in the assets/Image folder w/o
	/// 	extension.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfImage">	The user name of Image. </param>
	/// <param name="fileNameOfImage">	The file name of Image. </param>
	///-------------------------------------------------------------------------------------------------
	static void loadImage(std::string userNameOfImage, std::string userTextureName, float startX = 0.0f, float startY = 0.0f, float width = 0.0f, float height = 0.0f) { Instance().privateLoadImage(userNameOfImage, userTextureName, startX, startY, width, height); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Image from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfImage">	The user name of Image. </param>
	///-------------------------------------------------------------------------------------------------
	static void unloadSpecificImage(std::string userNameOfImage) { Instance().privateUnloadSpecificImage(userNameOfImage); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Images from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void unloadAllImages() { Instance().privateUnloadAllImages(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Image pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfImage">	The user name of Image. </param>
	///
	/// <returns>	Null if it fails, else the Image from map. </returns>
	///-------------------------------------------------------------------------------------------------
	static Image* getImageFromMap(std::string userNameOfImage) { return Instance().privateGetImageFromMap(userNameOfImage); };
};

#endif // !_ImageManager