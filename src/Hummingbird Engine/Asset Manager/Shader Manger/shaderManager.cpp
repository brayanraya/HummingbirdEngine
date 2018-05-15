#include "shaderManager.h"

shaderManager* shaderManager::currentInstanceShaderManager = nullptr;
std::map<std::string, ShaderObject*> shaderManager::mapOfUserNamesToPointers;

std::string shaderFolder = "Shaders/";

#define DEBUGOUT 1
void shaderManager::privateLoadDefaultShaders()
{
#if DEBUGOUT
	DebugMsg::out("Loading Default Shaders\n");
#endif // DEBUGOUT
}

void shaderManager::privateLoadShader(std::string userNameOfShader, const char * fileNameOfShader)
{
#if DEBUGOUT
	DebugMsg::out("Loading Shader: %s", userNameOfShader.c_str());
#endif //DEBUGOUT
	std::string completeDirectory(shaderFolder);
	if (mapOfUserNamesToPointers[userNameOfShader] == nullptr)
	{
		mapOfUserNamesToPointers[userNameOfShader] = new ShaderObject(completeDirectory.append(fileNameOfShader).c_str());
	}
	else
	{
#if DEBUGOUT
		DebugMsg::out("->Failed\n");
#endif 
		assert(false && "This name is already being used by another shader");
	}
#if DEBUGOUT
	DebugMsg::out("->Success\n");
#endif
}

void shaderManager::privateUnloadSpecificShader(std::string userNameOfShader)
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Shader: %s\n", userNameOfShader.c_str());
#endif
	//first delete the news
	delete mapOfUserNamesToPointers[userNameOfShader];
	//then remove from the map
	mapOfUserNamesToPointers.erase(userNameOfShader);
}

void shaderManager::privateUnloadAllShaders()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting All Shaders\n");
#endif
	//delete all shader pointers individually
	for (std::map<std::string, ShaderObject*>::iterator it = mapOfUserNamesToPointers.begin(); it != mapOfUserNamesToPointers.end(); ++it)
	{
#if DEBUGOUT
		DebugMsg::out("Deleting Shader: %s\n", it->first.c_str());
#endif
		delete it->second;
	}
	//Then clear the map
	mapOfUserNamesToPointers.clear();
	//final delete manager
	delete currentInstanceShaderManager;
	currentInstanceShaderManager = nullptr;
}

ShaderObject * shaderManager::privateGetShaderFromMap(std::string userNameOfShader)
{
	return mapOfUserNamesToPointers[userNameOfShader];
}

shaderManager::~shaderManager()
{
#if DEBUGOUT
	DebugMsg::out("\nDeleting Shader Manager\n");
#endif
}