#include "gameObjects.h"
#include "../Scene/scene.h"
#include "../Scene/sceneManager.h"

gameObjects::gameObjects()
{
	currentState = registrationState::currently_deregistered;
	this->pGameEntryCommand = new gameObjectsEntryCommand(this);
	this->pGameExitCommand = new gameObjectsExitCommand(this);
}

void gameObjects::connectToScene()
{
	assert(currentState == registrationState::pending_registration);
	sceneManager::getCurrentScene()->registerGameObject(this);
	currentState = registrationState::currently_registered;
}

void gameObjects::disconnectToScene()
{
	assert(currentState == registrationState::pending_deregistration);
	sceneManager::getCurrentScene()->deregisterGameObject(this);
	currentState = registrationState::currently_deregistered;
}

void gameObjects::submitEntry()
{
	assert(currentState == registrationState::currently_deregistered);
	sceneManager::getCurrentScene()->submitCommand(this->pGameEntryCommand);
	currentState = registrationState::pending_registration;
}

void gameObjects::submitExit()
{
	assert(currentState == registrationState::currently_registered);
	sceneManager::getCurrentScene()->submitCommand(this->pGameExitCommand);
	currentState = registrationState::pending_deregistration;
}
