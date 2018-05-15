#include "sceneManager.h"
#include "scene.h"
sceneManager* sceneManager::currentInstanceSceneManager = nullptr;

sceneManager::~sceneManager()
{
	endAllScenes();
}

void sceneManager::privSwapScenes()
{
	currentSceneManaged->sceneEnd();
	currentSceneManaged->myRegistrationBroker.executeCommands();
	delete currentSceneManaged;
	currentSceneManaged = nextSceneManged;
	nextSceneManged = nullptr;
	currentSceneManaged->initialize();
}

void sceneManager::privSetStartScene(scene* inputScene)
{
	currentSceneManaged = inputScene; 
	currentSceneManaged->initialize();
}

void sceneManager::privChangeCurrentScene(scene * inputScene)
{
	currentSceneManaged->prepareSwitch = true;
	nextSceneManged = inputScene;
}

void sceneManager::privEndAllScenes()
{
	currentSceneManaged->sceneEnd();
	if (nextSceneManged != nullptr)
	{
		nextSceneManged->sceneEnd();
	}
}

void sceneManager::privEndCurrentScene()
{
	currentSceneManaged->sceneEnd();
}
