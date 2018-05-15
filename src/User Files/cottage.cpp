#include "cottage.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

#include "cottageFactoryWithRecycling.h"
#include "bullet.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Visualizer.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"



cottage::cottage()
{
	pCottageTexture = new GraphicsObject_TextureFlat(modelManager::getModelFromMap("pModelCottage"), shaderManager::getShaderFromMap("pShaderObject_texture"), textureManager::getTextureFromMap("pBrickWallTex"), textureManager::getTextureFromMap("pRoofTextureTex"), textureManager::getTextureFromMap("pCabinTex"), textureManager::getTextureFromMap("pChimneyTex"));
	
	Matrix world = Matrix(SCALE, scaleFactor, scaleFactor, scaleFactor) * Matrix(TRANS, 50, 0, 50);
	pos = world;
	pCottageTexture->SetWorld(world);
	SetColliderModel(pCottageTexture->getModel());
	UpdateCollisionData(world, scaleFactor);
	submitEntry();
}

cottage::~cottage()
{
	delete pCottageTexture;
}

void cottage::sceneEntry()
{
	drawable::submitDrawableRegistration();
	checkForReg = true;
	collideable::submitCollideableRegistration<cottage>(this);
}

void cottage::sceneExit()
{
	if (checkForReg)
	{
		drawable::submitDrawableDeregistration();
	}
	collideable::submitCollideableDeregistration<cottage>(this);
}

void cottage::draw()
{
	pCottageTexture->Render(cameraManager::currentCam());
}

void cottage::collision(frigate *)
{
}

void cottage::collision(bullet * shot)
{
	health--;
	shot->sceneExit();
	if (health < 0)
	{
		sceneExit();
		cottageFactoryWithRecycling::Recyclecottage(this);
	}
}

void cottage::fromFactory(const Vect& inVec)
{
	level = 1000;
	health = 5;
	Matrix spot(SCALE, scaleFactor, scaleFactor, scaleFactor);
	spot *= Matrix(TRANS, inVec.X(), 0,inVec.Z());
	float x = (float)(rand() % int(level) + 100);
	float z = (float)(rand() % int(level) + 100);
	spot *= Matrix(TRANS, x, 0, z);
	pCottageTexture->SetWorld(spot);
	UpdateCollisionData(spot, scaleFactor);
}

void cottage::darkness(const Vect& inVec)
{
	drawable::submitDrawableDeregistration();
	if (level > 0)
	{
		level -= 100;
	}
	health++;
	Matrix spot(SCALE, scaleFactor, scaleFactor, scaleFactor);
	spot *= Matrix(TRANS, inVec.X(), 0, inVec.Z());
	float x = (float)(rand() % int(level) + 100);
	float z = (float)(rand() % int(level) + 100);
	spot *= Matrix(TRANS, x, 0, z);
	pCottageTexture->SetWorld(spot);
	UpdateCollisionData(spot, scaleFactor);
}

void cottage::lightness()
{
	drawable::submitDrawableRegistration();
	checkForReg = true;
}   