#include "EnemtBullet.h"

//#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
//#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
//#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
//#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"
//#include "../Hummingbird Engine/Scene Manager/Game Objects/gameObjects.h"
#include "EnemtBulletFactoryWithRecycling.h"
#include "frigate.h"
#include "hummingbirdCore.h"
#include "tank.h"
EnemyBullet::EnemyBullet()
{
	Vect Color(Color::Yellow);
	pGObj_BSphere = new GraphicsObject_WireframeConstantColor(modelManager::getModelFromMap("azulDefaultSphere"), shaderManager::getShaderFromMap("pShaderObject_constantColor"), Color);
	SetColliderModel(pGObj_BSphere->getModel());
	sceneEntry();
}

EnemyBullet::~EnemyBullet()
{
	delete pGObj_BSphere;
}

void EnemyBullet::sceneEntry()
{
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	alarmable::submitAlarmableRegistration(5.0f, alarmableManager::ALARM_ID::ALARM0);
	checkForAlarm = true;
	collideable::submitCollideableRegistration<EnemyBullet>(this);
}

void EnemyBullet::sceneExit()
{
	if (checkForAlarm)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
	updateable::submitUpdateableDeregistration();
	drawable::submitDrawableDeregistration();
	EnemyBulletFactoryWithRecycling::RecycleEnemtBullet(this);
	collideable::submitCollideableDeregistration<EnemyBullet>(this);
}

void EnemyBullet::fromFactory(const Vect& inPos, const Matrix& inRot)
{
	//fired = true;
	//ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	myRotation = inRot;
	myPostion = inPos;
	Matrix world = myRotation * Matrix(TRANS, myPostion);
	pGObj_BSphere->SetWorld(world);

}
void EnemyBullet::update()
{
		myPostion += Vect(0, 0, 1) * myRotation * EnemtBulletSpeed;
		Matrix world = myRotation * Matrix(TRANS, myPostion);
		pGObj_BSphere->SetWorld(world);
		UpdateCollisionData(world);
}

void EnemyBullet::draw()
{
	pGObj_BSphere->Render(cameraManager::currentCam());
}

void EnemyBullet::alarm0()
{
	checkForAlarm = false;
	sceneExit();
}

void EnemyBullet::collision(player *)
{
	sceneExit();
}

void EnemyBullet::collision(tank *)
{
	sceneExit();
}
