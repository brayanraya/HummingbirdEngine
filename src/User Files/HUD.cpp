#include "HUD.h"

#include "hummingbirdCore.h"

HUD::HUD()
{
	pGObj_Crosshair = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), shaderManager::getShaderFromMap("pShaderObject_sprite"), ImageManager::getImageFromMap("pImageGreen"), new Rect(0.0f, 0.0f, 200.0f, 200.0f));
	pGObj_Bullet = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), shaderManager::getShaderFromMap("pShaderObject_sprite"), ImageManager::getImageFromMap("pImageBullet"), new Rect(0.0f, 0.0f, 100.0f, 100.0f));
	pGObj_Num1 = new GraphicsObject_Sprite(modelManager::getModelFromMap("azulDefaultSquare"), shaderManager::getShaderFromMap("pShaderObject_sprite"), ImageManager::getImageFromMap("pImage1"), new Rect(0.0f, 0.0f, 100.0f, 100.0f));
	
	Matrix world(TRANS, (float)(hummingbirdEngine::getWindowWidth() / 10 * 9 + 75), (float)(hummingbirdEngine::getWindowHeight() / 10), 0);
	pGObj_Num1->SetWorld(world);
	world = Matrix(TRANS, (float)hummingbirdEngine::getWindowWidth()/2, (float)hummingbirdEngine::getWindowHeight()/2+20, 0); //x,y
	pGObj_Crosshair->SetWorld(world);	//place
	world = Matrix(ROT_Z,14.925f) * Matrix(TRANS, (float)(hummingbirdEngine::getWindowWidth()/10 *9), (float)(hummingbirdEngine::getWindowHeight() / 10), 0); //x,y
	pGObj_Bullet->SetWorld(world);

	spin = 0;

	submitEntry();
}

HUD::~HUD()
{
	delete pGObj_Crosshair;
	delete pGObj_Bullet;
	delete pGObj_Num1;
}

void HUD::sceneEntry()
{
	drawable::submitDrawableRegistration();
}

void HUD::sceneExit()
{
	drawable::submitDrawableDeregistration();
}

void HUD::drawHUD()
{
	spin += .05f;
	Matrix world = Matrix(ROT_Z, spin)* Matrix(TRANS, (float)hummingbirdEngine::getWindowWidth() / 2, (float)hummingbirdEngine::getWindowHeight() / 2 + 20, 0); //x,y

	pGObj_Crosshair->SetWorld(world);
	pGObj_Crosshair->Render(cameraManager::currentHUD());
	pGObj_Bullet->Render(cameraManager::currentHUD());
	pGObj_Num1->Render(cameraManager::currentHUD());
}
