#ifndef _modelManager
#define _modelManager

#include "AzulCore.h"
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for models loaded from file. </summary>
///
/// <remarks>	Braya, 3/2/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class modelManager //singleton
{
private:
	//------------------------------------
	//Big 4
	//------------------------------------
	modelManager() = default;
	~modelManager();
	modelManager(const modelManager&) = delete;
	modelManager& operator=(const modelManager&) = delete;



	//------------------------------------
	//Instance creator for the singleton
	//------------------------------------
	static modelManager& Instance()
	{
		if (!currentInstancemodelManager)
			currentInstancemodelManager = new modelManager;
		return *currentInstancemodelManager;
	};



	//------------------------------------
	//private Functions
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default models are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void privateLoadDefaultModels();

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided models to the map and allows that model to be accesssed by they key.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfModel">	The user name of model. </param>
	/// <param name="fileNameOfModel">	The file name of model. </param>
	///-------------------------------------------------------------------------------------------------

	void privateLoadModel(std::string userNameOfModel, const char * fileNameOfModel);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all models from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void privateUnloadAllModels();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific model from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfModel">	The user name of model. </param>
	///-------------------------------------------------------------------------------------------------

	static void privateUnloadSpecificModel(std::string userNameOfModel);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets model pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfModel">	The user name of model. </param>
	///
	/// <returns>	Null if it fails, else a pointer to a Model. </returns>
	///-------------------------------------------------------------------------------------------------

	Model* privateGetModelFromMap(std::string userNameOfModel);



	//------------------------------------
	//private variables
	//------------------------------------
	// 
	static modelManager* currentInstancemodelManager;
	static std::map<std::string, Model *> mapOfUserNamesToPointers;

public:
	//------------------------------------
	//Public API
	//------------------------------------

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Default models are automaticly loaded into the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void loadDefaultModels() { Instance().privateLoadDefaultModels(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>
	/// 	Adds provided models to the map and allows that model to be accesssed by they key The
	/// 	userNameOfmodel is the name the user will use when refering to the model The
	/// 	fileNameOfmodel is the name of the model as it appears in the assets/model folder w/o
	/// 	extension.
	/// </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfmodel">	The user name ofmodel. </param>
	/// <param name="fileNameOfmodel">	The file name ofmodel. </param>
	///-------------------------------------------------------------------------------------------------
	static void loadModel(std::string userNameOfmodel, const char * fileNameOfmodel) { Instance().privateLoadModel(userNameOfmodel, fileNameOfmodel); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes a specific model from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfmodel">	The user name ofmodel. </param>
	///-------------------------------------------------------------------------------------------------
	static void unloadSpecificModel(std::string userNameOfmodel) { Instance().privateUnloadSpecificModel(userNameOfmodel); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Removes all models from the map. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	static void unloadAllModels() { Instance().privateUnloadAllModels(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Gets model pointer from map and returns it to user. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="userNameOfmodel">	The user name ofmodel. </param>
	///
	/// <returns>	Null if it fails, else the model from map. </returns>
	///-------------------------------------------------------------------------------------------------
	static Model* getModelFromMap(std::string userNameOfmodel) { return Instance().privateGetModelFromMap(userNameOfmodel); };
};

#endif // !_modelManager