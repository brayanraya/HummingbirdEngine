#include "toySoldier.h"

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
	pToySoldier->SetWorld(world);
	SetColliderModel(pToySoldier->getModel(), collideableType::AABB);

	submitEntry();
}

EnemySoldier::~EnemySoldier()
{
	delete pToySoldier;
}

void EnemySoldier::sceneEntry()
{
	active = true;
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	collideable::submitCollideableRegistration<EnemySoldier>(this);
}

void EnemySoldier::sceneExit()
{
	if (active)
	{
		drawable::submitDrawableDeregistration();
		updateable::submitUpdateableDeregistration();
		collideable::submitCollideableDeregistration<EnemySoldier>(this);
	}
	if (numberShot)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
}

void EnemySoldier::draw()
{
	pToySoldier->Render(cameraManager::currentCam());
}

void EnemySoldier::update()
{
	UpdateCollisionData(world);
}

void EnemySoldier::alarm0()
{
	const Vect vectOffset = Vect(0.0f, 30.0f, 0.0f);
	//for triple shot
	if (numberShot < 3)
	{
		SoundManager::playSound("GunShot");
		EnemtBulletFactoryWithRecycling::CreateEnemtBullet(myPosition + vectOffset, myRotation);
		alarmable::submitAlarmableRegistration(0.1f, alarmableManager::ALARM_ID::ALARM0);
		numberShot++;
	}
	else
	{
		numberShot = 0;
	}

}

void EnemySoldier::collision(bullet *)
{
	health--;
	if (health == 0)
	{
		sceneExit();
		toySoldierFactoryWithRecycling::RecycletoySoldier(this);
	}
}

void EnemySoldier::fromFactory()
{
	health = 6;
	Matrix spot(SCALE, myScale, myScale, myScale);
	int fullArea = 1000; //unit
	myPosition = Vect((float)(rand() % fullArea) - fullArea /2, 3, (float)(rand() % fullArea) - fullArea / 2); //somewhere in the world
	spot *= Matrix(TRANS, myPosition);
	world = spot;
	pToySoldier->SetWorld(world);
	//UpdateCollisionData(world);
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
