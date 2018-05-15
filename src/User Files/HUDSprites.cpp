#include "HUDSprites.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Image Manger/imageManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

HUDSprites::HUDSprites()
{
	//DebugMsg::out("HUDSprites constructor\n");
	pGObj_HUDSprites1 = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), shaderManager::getShaderFromMap("pShaderObject_sprite"), ImageManager::getImageFromMap("pCrossSprite"), new Rect(0.0f, 0.0f, 150.0f, 150.0f));
	pGObj_HUDSprites2 = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), shaderManager::getShaderFromMap("pShaderObject_sprite"), ImageManager::getImageFromMap("pCottageSprite"), new Rect(0.0f, 0.0f, 50.0f, 50.0f));

	pos = Matrix(TRANS,960, 840, 0); //x,y

	submitEntry();
}

HUDSprites::~HUDSprites()
{
	//DebugMsg::out("HUDSprites destructor\n");

	delete pGObj_HUDSprites1;
	delete pGObj_HUDSprites2;
}

void HUDSprites::sceneEntry()
{
	drawable::submitDrawableRegistration();
}

void HUDSprites::sceneExit()
{
	drawable::submitDrawableDeregistration();
}

void HUDSprites::drawHUD()
{
	angle += 0.1f;
	rot.set(ROT_Z, angle);
	Matrix world = rot * pos;
	pGObj_HUDSprites1->SetWorld(world);
	pGObj_HUDSprites1->Render(cameraManager::currentHUD());
	float x = 50.0f;
	for (int i = 0; i < health; i++)
	{
		Matrix world2(TRANS, x, 50, 0); //x,y
		pGObj_HUDSprites2->SetWorld(world2);	//place
		pGObj_HUDSprites2->Render(cameraManager::currentHUD());
		x += 50;
	}
}
