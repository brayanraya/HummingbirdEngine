#include "worldPlane.h"

#include "../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../Hummingbird Engine/Render Manager/Camera Manager/cameraManager.h"

#include "frigate.h"

worldPlane::worldPlane()
{
	//DebugMsg::out("Plane constructor\n");
	pGObj_Plane = new GraphicsObject_TextureFlat(modelManager::getModelFromMap("pModelPlane"), shaderManager::getShaderFromMap("pShaderObject_texture"), textureManager::getTextureFromMap("pTextPlane"));
	Matrix world = Matrix(SCALE, 10000, 10000, 10000);
	pGObj_Plane->SetWorld(world);
	submitEntry();
}

worldPlane::~worldPlane()
{
	//DebugMsg::out("Plane destructor\n");
	delete pGObj_Plane;
}

void worldPlane::sceneEntry()
{
	drawable::submitDrawableRegistration();
	checkForReg = true;
}

void worldPlane::sceneExit()
{
	if (checkForReg)
	{
		drawable::submitDrawableDeregistration();
	}
}

void worldPlane::draw()
{
	pGObj_Plane->Render(cameraManager::currentCam());
}

void worldPlane::darkness()
{
	drawable::submitDrawableDeregistration();
	checkForReg = false;
}

void worldPlane::lightness()
{
	drawable::submitDrawableRegistration();
	checkForReg = true;
}