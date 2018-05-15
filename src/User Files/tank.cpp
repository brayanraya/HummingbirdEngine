#include "tank.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"
#include "../Hummingbird Engine/Asset Manager/Sound Manager/SoundManager.h"
#include "EnemySoldier.h"
#include "player.h"
#include "TankShellFactoryWithRecycling.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Visualizer.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"
#include "defaultScene.h"

tank::tank()
{
	pTankBodyTexture = new GraphicsObject_TextureFlat(modelManager::getModelFromMap("pModelT99B"), shaderManager::getShaderFromMap("pShaderObject_texture"), textureManager::getTextureFromMap("pT99BodyTex"), textureManager::getTextureFromMap("pT99BodyTex"), textureManager::getTextureFromMap("pT99BodyTex"), textureManager::getTextureFromMap("pT99BodyTex"));
	pTankTurretTexture = new GraphicsObject_TextureFlat(modelManager::getModelFromMap("pModelT99T"), shaderManager::getShaderFromMap("pShaderObject_texture"), textureManager::getTextureFromMap("pT99BodyTex"), textureManager::getTextureFromMap("pT99BodyTex"), textureManager::getTextureFromMap("pT99BodyTex"), textureManager::getTextureFromMap("pT99BodyTex"));


	myScale = Matrix(SCALE, bodyScaleFactor, bodyScaleFactor, bodyScaleFactor);
	myRotation = Matrix(IDENTITY);
	myBodyPosition = Vect(-200, 0, 0);
	myHeadPosition = Vect(-200, 40, -11);
	active = false;

	world = myScale * Matrix(TRANS, myHeadPosition);
	pTankTurretTexture->SetWorld(world);

	world = myScale * Matrix(TRANS, myBodyPosition);
	pTankBodyTexture->SetWorld(world);

	SetColliderModel(pTankBodyTexture->getModel(),collideableType::OBB);

	submitEntry();
}

tank::~tank()
{
	delete pTankBodyTexture;
	delete pTankTurretTexture;
}

void tank::sceneEntry()
{
	drawable::submitDrawableRegistration();
	collideable::submitCollideableRegistration<tank>(this);
	UpdateCollisionData(world);
}

void tank::sceneExit()
{
	drawable::submitDrawableDeregistration();
	if (active)
	{
		updateable::submitUpdateableDeregistration();
		inputable::submitInputableDeregistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
		inputable::submitInputableDeregistration(AZUL_KEY::KEY_2, INPUT_TYPE::PRESS);
		if (shot)
		{
			alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
		}
	}
	collideable::submitCollideableDeregistration<tank>(this);
}

void tank::draw()
{
	pTankBodyTexture->Render(cameraManager::currentCam());
	pTankTurretTexture->Render(cameraManager::currentCam());

}
void tank::update()
{
		// Ship translation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
		{
			myHeadPosition += Vect(0, 0, 1) * myRotation * TransSpeed;
			myBodyPosition += Vect(0, 0, 1) * myRotation * TransSpeed;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
		{
			myHeadPosition += Vect(0, 0, 1) * myRotation * -TransSpeed;
			myBodyPosition += Vect(0, 0, 1) * myRotation * -TransSpeed;
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
		world = myScale * myRotation * Matrix(TRANS, myBodyPosition);
		pTankBodyTexture->SetWorld(world);
		UpdateCollisionData(world);

		world = myScale * myRotation * Matrix(TRANS, myHeadPosition);
		pTankTurretTexture->SetWorld(world);
		exit->inTankPos(myBodyPosition);
		
		//Camera Updating -------------------------------
		Matrix worldMat = myRotation * Matrix(TRANS, myHeadPosition);  // This is the worldmat without scaling
		Vect vNewCamPos = Vect(0, 50, -75) * worldMat;		// This moves the cam position relative to guys's position and rotation
		Vect vNewLookAt = Vect(0, 45, 0) * worldMat;   // This moves the look-at point relative to guys's position and rotation
		cameraManager::setOrientAndPosition("default3D", Vect(0, 1, 0), vNewLookAt, vNewCamPos);
		//Camera Updating -------------------------------
}

void tank::keyPress(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
		if (!shot)
		{
			SoundManager::playSound("Shell");
			const Vect vectOffset = Vect(0.0f, 14.0f, 0.0f);
			TankShellFactoryWithRecycling::CreateTankShell(myHeadPosition+vectOffset, myRotation);
			alarmable::submitAlarmableRegistration(5.0f, alarmableManager::ALARM_ID::ALARM0);
			shot = true;
		}
	}
	if (k == AZUL_KEY::KEY_2)
	{
		if (exit != nullptr)
		{
			SoundManager::stopSound("Tank");
			updateable::submitUpdateableDeregistration();
			inputable::submitInputableDeregistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
			inputable::submitInputableDeregistration(AZUL_KEY::KEY_2, INPUT_TYPE::PRESS);
			exit->outOfRadius(myBodyPosition);
			exit = nullptr;
			active = false;
		}
	}
}

void tank::alarm0()
{
	shot = false;
}
void tank::collision(player* player)
{
	active = true;
	SoundManager::playSound("Tank", true);
	updateable::submitUpdateableRegistration();
	inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	inputable::submitInputableRegistration(AZUL_KEY::KEY_2, INPUT_TYPE::PRESS);
	exit = player;
}

void tank::collision(EnemyBullet *)
{
	health--;
	if (health <= 0)
	{
		sceneManager::changeCurrentScene(new startScene);
	}
}
