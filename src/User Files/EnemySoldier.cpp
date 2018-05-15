#include "EnemySoldier.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

#include "EnemtBulletFactoryWithRecycling.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Visualizer.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"

#include "irrKlang.h"
#include "../Hummingbird Engine/Asset Manager/Sound Manager/SoundManager.h"

#include "toySoldierFactoryWithRecycling.h"
#include "EnemtBullet.h"
#include "Bullet.h"
#include "TankShell.h"

EnemySoldier::EnemySoldier()
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pToySoldier = new GraphicsObject_TextureLight(	modelManager::getModelFromMap("pToySoldier"), 
													shaderManager::getShaderFromMap("pShaderObject_textureLight"), 
													textureManager::getTextureFromMap("pEnemyToySoldierTex"), 
													textureManager::getTextureFromMap("pEnemyToySoldierTex"), 
													textureManager::getTextureFromMap("pTextPlane"), 
													LightColor, 
													LightPos);
	myRotation = Matrix(IDENTITY);
	myPosition = Vect(0, 3, 0);
	world = Matrix(SCALE, myScale, myScale, myScale) * Matrix(TRANS, myPosition);
	//pToySoldier->SetWorld(world);
	SetColliderModel(pToySoldier->getModel(), collideableType::AABB);

	submitEntry();
}

EnemySoldier::~EnemySoldier()
{
	delete pToySoldier;
}

void EnemySoldier::sceneEntry()
{
	deltaX = 0;
	deltaZ = 0;
	numberShot = 0;
	health = 3;
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	collideable::submitCollideableRegistration<EnemySoldier>(this);
	alarm1();
	//alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM0);
}

void EnemySoldier::sceneExit()
{
	drawable::submitDrawableDeregistration();
	updateable::submitUpdateableDeregistration();
	collideable::submitCollideableDeregistration<EnemySoldier>(this);
	alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM1);
	toySoldierFactoryWithRecycling::RecycletoySoldier(this);
	if (numberShot)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
}

void EnemySoldier::draw()
{
	pToySoldier->Render(cameraManager::currentCam());
	
	if (health < 1)
	{
		sceneExit();
	}
}

void EnemySoldier::update()
{
	myPosition = Vect(myPosition.X() + deltaX, myPosition.Y(), myPosition.Z() + deltaZ);
	Matrix current(SCALE, myScale, myScale, myScale);
	world =	current * myRotation * Matrix(TRANS, myPosition);
	pToySoldier->SetWorld(world);
	UpdateCollisionData(world);
}

void EnemySoldier::alarm0()
{
	const Vect vectOffset = Vect(0.0f, 30.0f, 0.0f);
	//for triple shot
	if (numberShot < 3)
	{
		SoundManager::playSound("GunShot");
		EnemyBulletFactoryWithRecycling::CreateEnemtBullet(myPosition + vectOffset, myRotation);
		alarmable::submitAlarmableRegistration(0.1f, alarmableManager::ALARM_ID::ALARM0);
		numberShot++;
	}
	else
	{
		numberShot = 0;
	}

}
void EnemySoldier::alarm1()
{
	//move in a direction and switch randomly
	int val = rand() % 5;

	switch (val)
	{
	case 0:
		deltaX = -1.7f;
		break;
	case 1:
		deltaX = 1.7f;
		break;
	case 2:
		deltaX = 0;
		break;
	case 3:
		deltaZ = -0;
		break;
	case 4:
		deltaZ = 1.7f;
		break;
	case 5:
		deltaZ = -1.7f;
		break;
	default:
		break;
	}


	alarmable::submitAlarmableRegistration((float)(rand() % 10), alarmableManager::ALARM_ID::ALARM1);
}

void EnemySoldier::collision(bullet *)
{
	health--;
}

void EnemySoldier::collision(TankShell *)
{
	health = 0;
}

void EnemySoldier::fromFactory()
{
	health = 6;
	Matrix spot(SCALE, myScale, myScale, myScale);
	int fullArea = 100; //unit
	myPosition = Vect((float)(rand() % fullArea) - fullArea /2, 3, (float)(rand() % fullArea) - fullArea / 2); //somewhere in the world
	spot *= Matrix(TRANS, myPosition);
	world = spot;
	pToySoldier->SetWorld(world);
}

void EnemySoldier::TerrainCollision()
{
	//DebugMsg::out("Touching the Ground\n");
}

void EnemySoldier::FacePlayer(const Vect& playerPosition)
{
	Vect look = playerPosition - myPosition;

		look.norm();
		myRotation = Matrix(ROT_ORIENT, look, Vect(0, 1, 0));

		Matrix current(SCALE, myScale, myScale, myScale);
		current *= myRotation;
		current *= Matrix(TRANS, myPosition);
		world = current;
		pToySoldier->SetWorld(current);

		alarm0();
}
