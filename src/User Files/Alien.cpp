#include "Alien.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Image Manger/imageManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

Alien::Alien()
{
	//DebugMsg::out("Alien constructor\n");
	pGObj_Alien = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), shaderManager::getShaderFromMap("pShaderObject_sprite"), ImageManager::getImageFromMap("pImageGreen"), new Rect(100.0f, 0.0f, 150.0f, 150.0f));
	Matrix world(TRANS, 100, 100, 0); //x,y
	pGObj_Alien->SetWorld(world);	//place
	submitEntry();
}

Alien::~Alien()
{
	//DebugMsg::out("Alien destructor\n");

	delete pGObj_Alien;
}

void Alien::sceneEntry()
{
	drawable::submitDrawableRegistration();
}

void Alien::sceneExit()
{
	drawable::submitDrawableDeregistration();
}

void Alien::drawHUD()
{
	pGObj_Alien->Render(cameraManager::currentHUD());
}
