#include "../../Hummingbird Engine/Main Game/hummingbirdEngine.h"
#include "../../Hummingbird Engine/Asset Manager/Shader Manger/shaderManager.h"
#include "../../Hummingbird Engine/Asset Manager/Model Manger/modelManager.h"
#include "../../Hummingbird Engine/Asset Manager/Texture Manager/textureManager.h"
#include "../../Hummingbird Engine/Asset Manager/Image Manger/imageManager.h"
#include "../../Hummingbird Engine/Scene Manager/Scene/sceneManager.h"
#include "../../Hummingbird Engine/Asset Manager/Terrain Manager/terrainManager.h"
#include "../../Hummingbird Engine/Asset Manager/Sound Manager/SoundManager.h"

#include "../defaultScene.h"

void hummingbirdEngine::LoadUserResources()
{	
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	modelManager::loadModel("pModelPlane", "Plane.azul");
	modelManager::loadModel("pModelSpaceFrigate", "space_frigate.azul");
	modelManager::loadModel("pModelT99B", "t99body.azul");
	modelManager::loadModel("pModelT99T", "t99turret.azul");
	modelManager::loadModel("pToySoldier", "raya_toySoldier.azul");
	modelManager::loadModel("pTombstone", "tombstone.azul");

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------

	shaderManager::loadShader("pShaderObject_texture", "textureFlatRender");
	shaderManager::loadShader("pShaderObject_textureLight", "textureLightRender");
	shaderManager::loadShader("pShaderObject_constantColor", "colorConstantRender");
	shaderManager::loadShader("pShaderObject_colorNoTexture", "colorNoTextureRender");
	shaderManager::loadShader("pShaderObject_sprite", "spriteRender");


	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------
	
	textureManager::loadTexture("pSpaceFrigateTex", "space_frigate.tga");
	textureManager::loadTexture("pToySoldierTex", "raya_toySoldier.tga");
	textureManager::loadTexture("pEnemyToySoldierTex", "enemy_toySoldier.tga");
	textureManager::loadTexture("pTextPlane", "grass.tga");
	textureManager::loadTexture("pAliensTex", "crosshair.tga");
	textureManager::loadTexture("pBulletTex", "bulletIcon.tga");
	textureManager::loadTexture("pFontTex", "font.tga");
	textureManager::loadTexture("pT99BodyTex", "T99body.tga");
	textureManager::loadTexture("pT99TrackTex", "T99track.tga");
	textureManager::loadTexture("pTombstone", "Tombstone.tga");
	textureManager::loadTexture("pStartScreen", "StartScreen.tga");
	textureManager::loadTexture("pWelcomeCard", "WelcomeCard.tga");



	//---------------------------------------------------------------------------------------------------------
	// Load the Images
	//---------------------------------------------------------------------------------------------------------
	ImageManager::loadImage("pImageGreen", "pAliensTex");
	ImageManager::loadImage("pImageBullet", "pBulletTex");
	ImageManager::loadImage("pImage1", "pFontTex", 20,380,30,40);
	ImageManager::loadImage("pStartScreen", "pStartScreen");
	ImageManager::loadImage("pWelcomeCard", "pWelcomeCard");


	//---------------------------------------------------------------------------------------------------------
	// Load the Terrain
	//---------------------------------------------------------------------------------------------------------

	terrainManager::loadTerrain("pBumpy", "HMTest1.tga", "pTextPlane",10000);

	//---------------------------------------------------------------------------------------------------------
	// Load the Terrain
	//---------------------------------------------------------------------------------------------------------

	SoundManager::loadSound("GunShot", "Gunshot.wav");
	SoundManager::loadSound("FootSteps", "FootSteps.wav");
	SoundManager::loadSound("BackgroundRain", "BackgroundRain.wav");
	SoundManager::loadSound("Tank", "Tank.wav");
	SoundManager::loadSound("Shell", "Shell.wav");
	SoundManager::loadSound("TitleSong", "MainTitleSong.mp3");

	//---------------------------------------------------------------------------------------------------------
	// Load the Start Scene
	//---------------------------------------------------------------------------------------------------------

	sceneManager::setStartScene(new startScene);
}