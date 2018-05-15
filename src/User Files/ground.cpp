#include "ground.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

#include "frigate.h"

ground::ground()
{
	//DebugMsg::out("Plane constructor\n");
	pGObj_Plane = new GraphicsObject_TextureFlat(modelManager::getModelFromMap("pModelPlane"), shaderManager::getShaderFromMap("pShaderObject_texture"), textureManager::getTextureFromMap("pTextPlane"));
	Matrix world =  Matrix(SCALE, 10000.0f, 10000.0f, 10000.0f) * Matrix(TRANS,0,0,0);
	pGObj_Plane->SetWorld(world);
	submitEntry();
}

ground::~ground()
{
	//DebugMsg::out("Plane destructor\n");
	delete pGObj_Plane;
}

void ground::sceneEntry()
{
	drawable::submitDrawableRegistration();
}

void ground::sceneExit()
{
	drawable::submitDrawableDeregistration();
}

void ground::draw()
{
	pGObj_Plane->Render(cameraManager::currentCam());
}