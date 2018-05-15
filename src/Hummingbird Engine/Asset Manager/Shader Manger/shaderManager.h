#ifndef _shaderManager
#define _shaderManager

#include "AzulCore.h"
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for shaders loaded from file. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class shaderManager //singlton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	shaderManager() = default;
	~shaderManager();
	shaderManager(const shaderManager&) = delete;
	shaderManager& operator=(const shaderManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Instance creator for the singleton. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <returns>	A reference to a shaderManager. </returns>
	///-------------------------------------------------------------------------------------------------
	static shaderManager& Instance()
	{
		if (!currentInstanceShaderManager)
			currentInstanceShaderManager = new shaderManager;
		return *currentInstanceShaderManager;
	};


	//------------------------------------
	//private Functions
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default shaders are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateLoadDefaultShaders();

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided shaders to the map and allows that shader to be accesssed by they key.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfShader">	The user name of shader. </param>
	/// <param name="fileNameOfShader">	The file name of shader. </param>
	///-------------------------------------------------------------------------------------------------
	void privateLoadShader(std::string userNameOfShader, const char * fileNameOfShader);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all shaders from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void privateUnloadAllShaders();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific shader from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfShader">	The user name of shader. </param>
	///-------------------------------------------------------------------------------------------------
	static void privateUnloadSpecificShader(std::string userNameOfShader);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets shader pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfShader">	The user name of shader. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a ShaderObject. </returns>
	///-------------------------------------------------------------------------------------------------
	ShaderObject* privateGetShaderFromMap(std::string userNameOfShader);



	//------------------------------------
	//private variables
	//------------------------------------
	static shaderManager* currentInstanceShaderManager;
	static std::map<std::string, ShaderObject *> mapOfUserNamesToPointers;

public:
	///------------------------------------
	///Public API
	///------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default shaders are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void loadDefaultShaders() { Instance().privateLoadDefaultShaders(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided shaders to the map and allows that shader to be accesssed by they key The
	/// 	userNameOfShader is the name the user will use when refering to the shader The
	/// 	fileNameOfShader is the name of the shader as it appears in the assets/shader folder w/o
	/// 	extension.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfShader">	The user name of shader. </param>
	/// <param name="fileNameOfShader">	The file name of shader. </param>
	///-------------------------------------------------------------------------------------------------
	static void loadShader(std::string userNameOfShader, const char * fileNameOfShader) { Instance().privateLoadShader(userNameOfShader, fileNameOfShader); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific shader from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfShader">	The user name of shader. </param>
	///-------------------------------------------------------------------------------------------------
	static void unloadSpecificShader(std::string userNameOfShader) { Instance().privateUnloadSpecificShader(userNameOfShader); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all shaders from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void unloadAllShaders() { Instance().privateUnloadAllShaders(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets shader pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfShader">	The user name of shader. </param>
	///
	/// <returns>	Null if it fails, else the shader from map. </returns>
	///-------------------------------------------------------------------------------------------------
	static ShaderObject* getShaderFromMap(std::string userNameOfShader) { return Instance().privateGetShaderFromMap(userNameOfShader); };
};

#endif // !_shaderManager