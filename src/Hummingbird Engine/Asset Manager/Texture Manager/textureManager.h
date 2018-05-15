#ifndef _TextureManager
#define _TextureManager

#include "AzulCore.h"
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for textures loaded from file. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class textureManager // singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	textureManager() = default;
	~textureManager();
	textureManager(const textureManager&) = delete;
	textureManager& operator=(const textureManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a textureManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static textureManager& Instance()
	{
		if (!currentInstanceTextureManager)
			currentInstanceTextureManager = new textureManager;
		return *currentInstanceTextureManager;
	};


	//------------------------------------
	//private Functions
	//------------------------------------
	
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Textures are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void privateLoadDefaultTextures();

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided Textures to the map and allows that Texture to be accesssed by they key.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTexture">	The user name of texture. </param>
	/// <param name="fileNameOfTexture">	The file name of texture. </param>
	///-------------------------------------------------------------------------------------------------
	void privateLoadTexture(std::string userNameOfTexture, const char * fileNameOfTexture);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Textures from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void privateUnloadAllTextures();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Texture from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTexture">	The user name of texture. </param>
	///-------------------------------------------------------------------------------------------------
	static void privateUnloadSpecificTexture(std::string userNameOfTexture);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Texture pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTexture">	The user name of texture. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a Texture. </returns>
	///-------------------------------------------------------------------------------------------------
	Texture* privateGetTextureFromMap(std::string userNameOfTexture);

	//------------------------------------
	//private variables
	//------------------------------------
	static textureManager* currentInstanceTextureManager;
	static std::map<std::string, Texture *> mapOfUserNamesToPointers;

public:
	//------------------------------------
	//Public API
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default Textures are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void loadDefaultTextures() { Instance().privateLoadDefaultTextures(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided Textures to the map and allows that Texture to be accesssed by they key The
	/// 	userNameOfTexture is the name the user will use when refering to the Texture The
	/// 	fileNameOfTexture is the name of the Texture as it appears in the assets/Texture folder
	/// 	w/o extension.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTexture">	The user name of texture. </param>
	/// <param name="fileNameOfTexture">	The file name of texture. </param>
	///-------------------------------------------------------------------------------------------------
	static void loadTexture(std::string userNameOfTexture, const char * fileNameOfTexture) { Instance().privateLoadTexture(userNameOfTexture, fileNameOfTexture); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific Texture from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTexture">	The user name of texture. </param>
	///-------------------------------------------------------------------------------------------------
	static void unloadSpecificTexture(std::string userNameOfTexture) { Instance().privateUnloadSpecificTexture(userNameOfTexture); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all Textures from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void unloadAllTextures() { Instance().privateUnloadAllTextures(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets Texture pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfTexture">	The user name of texture. </param>
	///
	/// <returns>	Null if it fails, else the texture from map. </returns>
	///-------------------------------------------------------------------------------------------------
	static Texture* getTextureFromMap(std::string userNameOfTexture) { return Instance().privateGetTextureFromMap(userNameOfTexture); };
};

#endif // !_TextureManager