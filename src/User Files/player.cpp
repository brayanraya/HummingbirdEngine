#include "player.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

#include "bulletFactoryWithRecycling.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Visualizer.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"

#include "irrKlang.h"
#include "../Hummingbird Engine/Asset Manager/Sound Manager/SoundManager.h"
#include "defaultScene.h"
player::player()
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);

	pplayer = new GraphicsObject_TextureLight(modelManager::getModelFromMap("pToySoldier"),
		shaderManager::getShaderFromMap("pShaderObject_textureLight"),
		textureManager::getTextureFromMap("pToySoldierTex"),
		textureManager::getTextureFromMap("pToySoldierTex"),
		textureManager::getTextureFromMap("pTextPlane"),
		LightColor,
		LightPos);

	myScale = Matrix(SCALE, 15.0f, 15.0f, 15.0f);
	myRotation = Matrix(IDENTITY);
	myPosition = Vect(900, 3, 500);
	health = 10;
	active = true;

	world = myScale * Matrix(TRANS, myPosition);
	pplayer->SetWorld(world);
	SetColliderModel(pplayer->getModel(),collideableType::AABB);
	
	submitEntry();
}

player::~player()
{
	delete pplayer;
}

void player::sceneEntry()
{
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	collideable::submitCollideableRegistration<player>(this);
	UpdateCollisionData(world);
}

void player::sceneExit()
{
	if (active)
	{
		drawable::submitDrawableDeregistration();
		updateable::submitUpdateableDeregistration();
		inputable::submitInputableDeregistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
		collideable::submitCollideableDeregistration<player>(this);
	}
	if (numberShot)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
}

void player::draw()
{
	pplayer->Render(cameraManager::currentCam());
}

void player::update()
{
		// Ship translation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			myPosition += Vect(0, 0, 1) * myRotation * TransSpeed;
			SoundManager::playSound("FootSteps", true);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			myPosition += Vect(0, 0, 1) * myRotation * -TransSpeed;
			SoundManager::playSound("FootSteps", true);
		}
		else
		{
			SoundManager::stopSound("FootSteps");
		}

		// Ship Rotation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
		{
			myRotation *= Matrix(ROT_Y, ShipRotAng);
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
		{
			myRotation *= Matrix(ROT_Y, -ShipRotAng);
		}

		// Spaceship adjust matrix
		world = myScale * myRotation * Matrix(TRANS, myPosition);
		pplayer->SetWorld(world);
		UpdateCollisionData(world);

		//Camera Updating -------------------------------
		Matrix worldMat = myRotation * Matrix(TRANS, myPosition);  // This is the worldmat without scaling
		Vect vNewCamPos = Vect(0, 50, -75) * worldMat;		// This moves the cam position relative to guys's position and rotation
		Vect vNewLookAt = Vect(0, 45, 0) * worldMat;   // This moves the look-at point relative to guys's position and rotation
		cameraManager::setOrientAndPosition("default3D", Vect(0, 1, 0), vNewLookAt, vNewCamPos);
		//Camera Updating -------------------------------
}

void player::keyPress(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
			if (!numberShot)
			{
				alarm0();
			}
	}
}

void player::keyRelease(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
	}
}
void player::outOfRadius(const Vect & inVec)
{
	Vect offset(500, 0, 0);
	myPosition = inVec + offset;
	world = myScale * Matrix(TRANS, myPosition);
	pplayer->SetWorld(world);
	SetColliderModel(pplayer->getModel(),collideableType::BSPHERE);
	active = true;
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	collideable::submitCollideableRegistration<player>(this);
}
void player::alarm0()
{
	const Vect vectOffset = Vect(0.0f, 30.0f, 0.0f);
	//for triple shot
	if (numberShot < 3)
	{
		SoundManager::playSound("GunShot");
		bulletFactoryWithRecycling::Createbullet(myPosition + vectOffset, myRotation);
		alarmable::submitAlarmableRegistration(0.1f, alarmableManager::ALARM_ID::ALARM0);
		numberShot++;
	}
	else
	{
		numberShot = 0;
	}

}

void player::inTankPos(const Vect & inMat)
{
	myPosition = inMat;
}

void player::collision(EnemyBullet *)
{
	health--;
	if (health <= 0)
	{
		sceneManager::changeCurrentScene(new startScene);
	}
}
void player::collision(tank *)
{
	active = false;
	SoundManager::stopSound("FootSteps");
	drawable::submitDrawableDeregistration();
	updateable::submitUpdateableDeregistration();
	inputable::submitInputableDeregistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	collideable::submitCollideableDeregistration<player>(this);
}

void player::TerrainCollision()
{
	//DebugMsg::out("Touching the Ground\n");
}

const Vect player::getPos() const
{
	return myPosition;
}
