#include "drawable.h"
#include "../../Scene/scene.h"
#include "../../Scene/sceneManager.h"
#include "../Drawable/drawableRegistratonCommand.h"
#include "../Drawable/drawableDeregistratonCommand.h"

drawable::drawable()
{
	pRegistrationCmd = new drawableRegistratonCommand(this);
	pDeregistrationCmd = new drawableDeregistratonCommand(this);
	currentState = registrationState::currently_deregistered;
}

drawable::~drawable()
{
}

void drawable::sceneDeregistraion()
{
	assert(currentState == registrationState::pending_deregistration);
	sceneManager::getCurrentScene()->deregisterDrawable(this);
	currentState = registrationState::currently_deregistered;
}

void drawable::sceneRegistraion()
{
	assert(currentState == registrationState::pending_registration);
	sceneManager::getCurrentScene()->registerDrawable(this);
	currentState = registrationState::currently_registered;
}

void drawable::submitDrawableDeregistration()
{
	assert(currentState == registrationState::currently_registered);
	sceneManager::getCurrentScene()->submitCommand(pDeregistrationCmd);
	currentState = registrationState::pending_deregistration;

}

void drawable::submitDrawableRegistration()
{
	assert(currentState == registrationState::currently_deregistered);
	sceneManager::getCurrentScene()->submitCommand(pRegistrationCmd);
	currentState = registrationState::pending_registration;

}
