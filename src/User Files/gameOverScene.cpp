#include "gameOverScene.h"
#include "frigate.h"
#include "../Hummingbird Engine/Scene Manager/Scene/sceneManager.h"
#include "userScene.h"

gameOverScene::gameOverScene()
{
	//DebugMsg::out("DEFAULT SCENE CONSTRUCTOR\n");
}

gameOverScene::~gameOverScene()
{
	//DebugMsg::out("DEFAULT SCENE DESTRUCTOR\n");
}

void gameOverScene::initialize()
{
	//DebugMsg::out("ENTERING DEFAULT SCENE\n");
	inputable::submitInputableRegistration(AZUL_KEY::KEY_ENTER, INPUT_TYPE::RELEASE);
}

void gameOverScene::keyPress(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_ENTER)
	{
	}
}

void gameOverScene::keyRelease(AZUL_KEY k)
{	
	if (k == AZUL_KEY::KEY_ENTER)
	{
		sceneManager::changeCurrentScene(new userScene);
	}
}

void gameOverScene::sceneEntry()
{
}

void gameOverScene::sceneExit()
{
}

void gameOverScene::sceneEnd()
{
	//DebugMsg::out("EXITING DEFAULT SCENE\n");
	inputable::submitInputableDeregistration(AZUL_KEY::KEY_ENTER, INPUT_TYPE::RELEASE);
}