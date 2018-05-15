#include "modelManager.h"

modelManager* modelManager::currentInstancemodelManager = nullptr;
std::map<std::string, Model*> modelManager::mapOfUserNamesToPointers;


#define DEBUGOUT 1
void modelManager::privateLoadDefaultModels()
{
#if DEBUGOUT
	DebugMsg::out("Loading Default Models\n");
#endif
	mapOfUserNamesToPointers[std::string("azulDefaultSphere")] = new Model(Model::PreMadedeModels::UnitSphere);
	mapOfUserNamesToPointers[std::string("azulDefaultBox")] = new Model(Model::PreMadedeModels::UnitBox_WF);
	mapOfUserNamesToPointers[std::string("azulDefaultSquare")] = new Model(Model::PreMadedeModels::UnitSquareXY);
}

void modelManager::privateLoadModel(std::string userNameOfModel, const char * fileNameOfmodel)
{
#if DEBUGOUT
	DebugMsg::out("Loading model: %s", userNameOfModel.c_str());
#endif 
	if (mapOfUserNamesToPointers[userNameOfModel] == nullptr)
	{
		std::string completeDirectory = "Models/";
		mapOfUserNamesToPointers[userNameOfModel] = new Model(completeDirectory.append(fileNameOfmodel).c_str());
	}
	else
	{
#if DEBUGOUT
		DebugMsg::out("->Failed\n");
#endif
		assert(false && "This name is already being used by another model");
	}
#if DEBUGOUT
	DebugMsg::out("->Success\n");
#endif
}

void modelManager::privateUnloadSpecificModel(std::string userNameOfModel)
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting model: %s\n", userNameOfModel.c_str());
#endif
	//first delete the news
	delete mapOfUserNamesToPointers[userNameOfModel];
	//then remove from the map
	mapOfUserNamesToPointers.erase(userNameOfModel);
}

void modelManager::privateUnloadAllModels()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting All models\n");
#endif
	//delete all model pointers individually
	for (std::map<std::string, Model*>::iterator it = mapOfUserNamesToPointers.begin(); it != mapOfUserNamesToPointers.end(); ++it)
	{
#if DEBUGOUT
		DebugMsg::out("Deleting model: %s\n", it->first.c_str());
#endif
		delete it->second;
	}
	//Then clear the map
	mapOfUserNamesToPointers.clear();
	//final delete manager
	delete currentInstancemodelManager;
	currentInstancemodelManager = nullptr;
}

Model * modelManager::privateGetModelFromMap(std::string userNameOfModel)
{
	return mapOfUserNamesToPointers[userNameOfModel];
}

modelManager::~modelManager()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting model Manager\n");
#endif

}