#include "bullet.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"
#include "../Hummingbird Engine/Scene Manager/Game Objects/gameObjects.h"
#include "bulletFactoryWithRecycling.h"
#include "frigate.h"

bullet::bullet()
{
	Vect Red(1.0f, 0.0f, 0.0f, 1.0f);
	pGObj_BSphere = new GraphicsObject_WireframeConstantColor(modelManager::getModelFromMap("azulDefaultSphere"), shaderManager::getShaderFromMap("pShaderObject_constantColor"), Red);
	SetColliderModel(pGObj_BSphere->getModel());
	sceneEntry();
}

bullet::~bullet()
{
	delete pGObj_BSphere;
}

void bullet::sceneEntry()
{
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	alarmable::submitAlarmableRegistration(5.0f, alarmableManager::ALARM_ID::ALARM0);
	checkForAlarm = true;
	collideable::submitCollideableRegistration<bullet>(this);
}

void bullet::sceneExit()
{
	if (checkForAlarm)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
	updateable::submitUpdateableDeregistration();
	drawable::submitDrawableDeregistration();
	bulletFactoryWithRecycling::Recyclebullet(this);
	collideable::submitCollideableDeregistration<bullet>(this);
}

void bullet::fromFactory(const Vect& inPos, const Matrix& inRot)
{
	//fired = true;
	//ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	myRotation = inRot;
	myPostion = inPos;
	Matrix world = myRotation * Matrix(TRANS, myPostion);
	pGObj_BSphere->SetWorld(world);

}
void bullet::update()
{
		myPostion += Vect(0, 0, 1) * myRotation * bulletSpeed;
		Matrix world = myRotation * Matrix(TRANS, myPostion);
		pGObj_BSphere->SetWorld(world);
		UpdateCollisionData(world);
}

void bullet::draw()
{
	pGObj_BSphere->Render(cameraManager::currentCam());
}

void bullet::alarm0()
{
	checkForAlarm = false;
	sceneExit();
}

void bullet::collision(EnemySoldier *)
{
	sceneExit();
}
