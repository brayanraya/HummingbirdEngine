#include "inputable.h"
#include "../../Scene/scene.h"
#include "../../Scene/sceneManager.h"
#include "../inputable/inputableRegistratonCommand.h"
#include "../inputable/inputableDeregistratonCommand.h"
#include "../../../Main Game/hummingbirdEngine.h"
#include "Keyboard.h"
#include "../inputable/singleKeyEventManager.h"

inputable::inputable()
{
}

inputable::~inputable()
{
	//fix
}

void inputable::sceneDeregistraion(AZUL_KEY inKey, INPUT_TYPE inType)
{
	std::pair<AZUL_KEY, INPUT_TYPE> temp(inKey, inType);
	if (inType == INPUT_TYPE::PRESS)
	{
		assert((inputableMapOfKeys[temp])->currentState == registrationState::pending_deregistration);
		sceneManager::getCurrentScene()->deregisterInputable(this, inKey,inType);
		(inputableMapOfKeys[temp])->currentState = registrationState::currently_deregistered;
	}
	else
	{
		assert((inputableMapOfKeys[temp])->currentState == registrationState::pending_deregistration);
		sceneManager::getCurrentScene()->deregisterInputable(this, inKey, inType);
		(inputableMapOfKeys[temp])->currentState = registrationState::currently_deregistered;
	}
}

void inputable::sceneRegistraion(AZUL_KEY inKey, INPUT_TYPE inType)
{
	std::pair<AZUL_KEY, INPUT_TYPE> temp(inKey, inType);
	if (inType == INPUT_TYPE::PRESS)
	{
		assert((inputableMapOfKeys[temp])->currentState == registrationState::pending_registration);
		sceneManager::getCurrentScene()->registerInputable(this, temp);
		(inputableMapOfKeys[temp])->currentState = registrationState::currently_registered;
	}
	else
	{
		assert((inputableMapOfKeys[temp])->currentState == registrationState::pending_registration);
		sceneManager::getCurrentScene()->registerInputable(this, temp);
		(inputableMapOfKeys[temp])->currentState = registrationState::currently_registered;
	}
}

void inputable::submitInputableDeregistration(AZUL_KEY inKey, INPUT_TYPE inType)
{
	KeyEvent temp(inKey, inType);
	if (inType == INPUT_TYPE::PRESS)
	{
		assert(inputableMapOfKeys[temp]->currentState == registrationState::currently_registered);
		sceneManager::getCurrentScene()->submitCommand(inputableMapOfKeys[temp]->pDeregistrationCmd);
		inputableMapOfKeys[temp]->currentState = registrationState::pending_deregistration;
	}
	else
	{
		assert(inputableMapOfKeys[temp]->currentState == registrationState::currently_registered);
		sceneManager::getCurrentScene()->submitCommand(inputableMapOfKeys[temp]->pDeregistrationCmd);
		inputableMapOfKeys[temp]->currentState = registrationState::pending_deregistration;
	}
}

void inputable::submitInputableRegistration(AZUL_KEY inKey, INPUT_TYPE inType)
{
	KeyEvent temp(inKey, inType);
	if (inputableMapOfKeys[temp] == nullptr)
	{
		RegistrationData* dataTemp = new RegistrationData();
		dataTemp->currentState = registrationState::currently_deregistered;
		dataTemp->pRegistrationCmd = new inputableRegistratonCommand(this, inKey, inType);
		dataTemp->pDeregistrationCmd = new inputableDeregistratonCommand(this, inKey, inType);
		dataTemp->theEvent = temp;
		inputableMapOfKeys[temp] = dataTemp;
	}
	assert((inputableMapOfKeys[temp])->currentState == registrationState::currently_deregistered);
	sceneManager::getCurrentScene()->submitCommand((inputableMapOfKeys[temp])->pRegistrationCmd);
	(inputableMapOfKeys[temp])->currentState = registrationState::pending_registration;
}
