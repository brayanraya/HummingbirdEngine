#include "frigate.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"
#include "../Hummingbird Engine/Scene Manager/Game Objects/gameObjects.h"
#include "bulletFactoryWithRecycling.h"
#include "EnemySoldier.h"
#include "player.h"
#include "defaultScene.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Visualizer.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"

frigate::frigate()
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(modelManager::getModelFromMap("pModelSpaceFrigate"), shaderManager::getShaderFromMap("pShaderObject_textureLight"), textureManager::getTextureFromMap("pSpaceFrigateTex"), LightColor, LightPos);

	// Spaceship
	myScale.set(SCALE, ScaleFactor, ScaleFactor, ScaleFactor);
	myRot.set(IDENTITY);
	myPosition.set(200, 30, 200);
	world = myScale * myRot * Matrix(TRANS, myPosition);
	pGObj_SpaceFrigateLight->SetWorld(world);
	SetColliderModel(pGObj_SpaceFrigateLight->getModel(),collideableType::OBB);

	submitEntry();
}

frigate::frigate(const Vect& inPos)
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(modelManager::getModelFromMap("pModelSpaceFrigate"), shaderManager::getShaderFromMap("pShaderObject_textureLight"), textureManager::getTextureFromMap("pSpaceFrigateTex"), LightColor, LightPos);

	// Spaceship
	myScale.set(SCALE, ScaleFactor, ScaleFactor, ScaleFactor);
	myRot.set(IDENTITY);
	myPosition.set(inPos);
	world = myScale * myRot * Matrix(TRANS, myPosition);
	pGObj_SpaceFrigateLight->SetWorld(world);
	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), collideableType::OBB);

	sceneEntry1();
}

void frigate::sceneEntry()
{
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::RELEASE);
	inputable::submitInputableRegistration(AZUL_KEY::KEY_R, INPUT_TYPE::RELEASE);
	collideable::submitCollideableRegistration<frigate>(this);
	UpdateCollisionData(world);
}

void frigate::sceneExit()
{
	inputable::submitInputableDeregistration(AZUL_KEY::KEY_R, INPUT_TYPE::RELEASE);
	inputable::submitInputableDeregistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::RELEASE);
	inputable::submitInputableDeregistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	updateable::submitUpdateableDeregistration();
	drawable::submitDrawableDeregistration();
	collideable::submitCollideableDeregistration<frigate>(this);
}

void frigate::sceneEntry1()
{
	drawable::submitDrawableRegistration();
	updateable::submitUpdateableRegistration();
	collideable::submitCollideableRegistration<frigate>(this);
	UpdateCollisionData(world);
}

void frigate::sceneExit1()
{
	updateable::submitUpdateableDeregistration();
	drawable::submitDrawableDeregistration();
	collideable::submitCollideableDeregistration<frigate>(this);
}

void frigate::update()
{
}

void frigate::draw()
{
	pGObj_SpaceFrigateLight->Render(cameraManager::currentCam());
}

void frigate::keyPress(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
	}
}

void frigate::keyRelease(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_SPACE)
	{
	}
	if (k == AZUL_KEY::KEY_R)
	{
		if (toggleCam)
		{
			cameraManager::switchToGodCam();
			toggleCam = false;
		}
		else
		{
			cameraManager::switchOffGodCam();
			toggleCam = true;
		}
	}
}

void frigate::collision(bullet *)
{
}

void frigate::collision(player *)
{
}

frigate::~frigate()
{
	delete pGObj_SpaceFrigateLight;
}
