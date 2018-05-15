#include "TankShell.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"
#include "../Hummingbird Engine/Scene Manager/Game Objects/gameObjects.h"
#include "frigate.h"

TankShell::TankShell()
{
	Vect Red(1.0f, 0.0f, 0.0f, 1.0f);
	pGObj_BSphere = new GraphicsObject_WireframeConstantColor(modelManager::getModelFromMap("azulDefaultSphere"), shaderManager::getShaderFromMap("pShaderObject_constantColor"), Red);
	SetColliderModel(pGObj_BSphere->getModel());
	sceneEntry();
}

TankShell::~TankShell()
{
	delete pGObj_BSphere;
}

void TankShell::sceneEntry()
{
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	alarmable::submitAlarmableRegistration(5.0f, alarmableManager::ALARM_ID::ALARM0);
	alarmable::submitAlarmableRegistration(0.5f, alarmableManager::ALARM_ID::ALARM1);
	checkForAlarm = true;
	checkForAlarm2 = true;
	collideable::submitCollideableRegistration<TankShell>(this);
}

void TankShell::sceneExit()
{
	if (checkForAlarm)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
	if (checkForAlarm2)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM1);
	}
	updateable::submitUpdateableDeregistration();
	drawable::submitDrawableDeregistration();
	collideable::submitCollideableDeregistration<TankShell>(this);
}

void TankShell::fromFactory(const Vect& inPos, const Matrix& inRot)
{
	Matrix temp(SCALE, scaleFactor, scaleFactor, scaleFactor);
	myRotation = inRot;
	myPostion = inPos;
	Matrix world = temp * myRotation * Matrix(TRANS, myPostion);
	pGObj_BSphere->SetWorld(world);

}
void TankShell::update()
{
		Matrix temp(SCALE, scaleFactor, scaleFactor, scaleFactor);
		myPostion += Vect(0, 0, 1) * myRotation * TankShellSpeed;
		Matrix world =  temp *myRotation * Matrix(TRANS, myPostion);
		pGObj_BSphere->SetWorld(world);
		UpdateCollisionData(world);
}

void TankShell::draw()
{
	pGObj_BSphere->Render(cameraManager::currentCam());
}

void TankShell::alarm0()
{
	checkForAlarm = false;
	sceneExit();
}
void TankShell::alarm1()
{
	scaleFactor *= 1.5f;
	checkForAlarm2 = false;
	alarmable::submitAlarmableRegistration(0.5f, alarmableManager::ALARM_ID::ALARM1);
}

void TankShell::collision(EnemySoldier *)
{
	sceneExit();
}
