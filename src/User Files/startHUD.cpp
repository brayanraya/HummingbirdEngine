#include "startHUD.h"

#include "hummingbirdCore.h"

startHUD::startHUD()
{
	pGObj_Splash = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), 
												shaderManager::getShaderFromMap("pShaderObject_sprite"), 
												ImageManager::getImageFromMap("pStartScreen"), 
												new Rect(0.0f, 0.0f, (float)hummingbirdEngine::getWindowWidth(), (float)hummingbirdEngine::getWindowHeight()));

	pGObj_Letter= new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"),
		shaderManager::getShaderFromMap("pShaderObject_sprite"),
		ImageManager::getImageFromMap("pWelcomeCard"),
		new Rect(0.0f, 0.0f, (float)hummingbirdEngine::getWindowWidth(), (float)hummingbirdEngine::getWindowHeight()));

	Matrix world(TRANS, (float)(hummingbirdEngine::getWindowWidth())/2, (float)(hummingbirdEngine::getWindowHeight())/2, 0);
	pGObj_Splash->SetWorld(world);	//place
	pGObj_Letter->SetWorld(world);	//place


	submitEntry();
}

startHUD::~startHUD()
{
	delete pGObj_Splash;
	delete pGObj_Letter;

}

void startHUD::sceneEntry()
{
	drawable::submitDrawableRegistration();
	isSplash = true;
}

void startHUD::sceneExit()
{
	drawable::submitDrawableDeregistration();
}

void startHUD::drawHUD()
{
	if (isSplash)
	{
		pGObj_Splash->Render(cameraManager::currentHUD());
	}
	else
	{
		pGObj_Letter->Render(cameraManager::currentHUD());
	}
}

void startHUD::switchScreen ()
{
	isSplash = false;
}

bool startHUD::currentScreen()
{
	return isSplash;
}
