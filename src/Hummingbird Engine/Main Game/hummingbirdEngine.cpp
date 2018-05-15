#include "AzulCore.h"
#include "hummingbirdEngine.h"

#include "../Asset Manager/Shader Manger/shaderManager.h"
#include "../Asset Manager/Model Manger/modelManager.h"
#include "../Asset Manager/Texture Manager/textureManager.h"
#include "../Render Manager/Camera Manager/cameraManager.h"
#include "../Scene Manager/Scene/scene.h"
#include "../Scene Manager/Scene/sceneManager.h"
#include "../Time/Time Manager/timeManager.h"
#include "../Asset Manager/Image Manger/imageManager.h"
#include "../Asset Manager/Terrain Manager/terrainManager.h"
#include "../Asset Manager/Sound Manager/SoundManager.h"

hummingbirdEngine* hummingbirdEngine::currentInstanceGame = nullptr;

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void hummingbirdEngine::Initialize()
{
	this->LoadUserSettings();
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void hummingbirdEngine::LoadContent()
{
	modelManager::loadDefaultModels();
	shaderManager::loadDefaultShaders();
	textureManager::loadDefaultTextures();
	cameraManager::loadDefaultCameras();

	this->LoadUserResources();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void hummingbirdEngine::Update()
{
	if (cameraManager::isGodCamOn())
	{
		cameraManager::controlGodCam();
	}

	char title[100]; // probably overkill
	timeManager::processTime(GetTimeInSeconds());
	sprintf_s(title , 100, "Hummingbird Engine -currentTime:%f  -frameTime:%f   -FPS:%d", timeManager::getCurrentTime(),timeManager::getFrameNumber(),timeManager::getFPS());
	glfwSetWindowTitle(&title[0]);

	sceneManager::getCurrentScene()->update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void hummingbirdEngine::Draw()
{
	sceneManager::getCurrentScene()->draw();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void hummingbirdEngine::UnLoadContent()
{
	// general clean up.
	sceneManager::endAllScenes();
	modelManager::unloadAllModels();
	shaderManager::unloadAllShaders();
	textureManager::unloadAllTextures();
	cameraManager::unloadAllCameras();
	ImageManager::unloadAllImages();
	terrainManager::unloadAllTerrains();
	SoundManager::unloadAllSounds();
}

hummingbirdEngine::~hummingbirdEngine()
{
	delete currentInstanceGame;
	currentInstanceGame = nullptr;
}



