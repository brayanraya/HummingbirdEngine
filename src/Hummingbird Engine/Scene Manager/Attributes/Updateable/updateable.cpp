#include "updateable.h"
#include "../../Scene/scene.h"
#include "../../Scene/sceneManager.h"
#include "../updateable/updateableRegistratonCommand.h"
#include "../updateable/updateableDeregistratonCommand.h"

updateable::updateable()
{
	pRegistrationCmd = new updateableRegistratonCommand(this);
	pDeregistrationCmd = new updateableDeregistratonCommand(this);
	currentState = registrationState::currently_deregistered;
}

updateable::~updateable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

void updateable::sceneDeregistraion()
{
	assert(currentState == registrationState::pending_deregistration);
	sceneManager::getCurrentScene()->deregisterUpdateable(this);
	currentState = registrationState::currently_deregistered;
}

void updateable::sceneRegistraion()
{
	assert(currentState == registrationState::pending_registration);
	sceneManager::getCurrentScene()->registerUpdateable(this);
	currentState = registrationState::currently_registered;
}

void updateable::submitUpdateableDeregistration()
{
	assert(currentState == registrationState::currently_registered);
	sceneManager::getCurrentScene()->submitCommand(pDeregistrationCmd);
	currentState = registrationState::pending_deregistration;

}

void updateable::submitUpdateableRegistration()
{
	assert(currentState == registrationState::currently_deregistered);
	sceneManager::getCurrentScene()->submitCommand(pRegistrationCmd);
	currentState = registrationState::pending_registration;

}
