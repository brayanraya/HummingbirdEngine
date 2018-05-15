#include "defaultScene.h"

#include "hummingbirdCore.h"

#include "userScene.h"
#include "startHUD.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

void startScene::initialize()
{
	DebugMsg::out("ENTERING DEFAULT SCENE\n");
	SoundManager::playSound("TitleSong", true);
	img = new startHUD;
	inputable::submitInputableRegistration(AZUL_KEY::KEY_ENTER, INPUT_TYPE::RELEASE);
}

void startScene::keyPress(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_ENTER)
	{
	}
}

void startScene::keyRelease(AZUL_KEY k)
{	
	if (k == AZUL_KEY::KEY_ENTER)
	{
		if (!img->currentScreen())
		{
			sceneManager::changeCurrentScene(new userScene);
		}
		else
		{
			img->switchScreen();
		}
	}
}

void startScene::sceneEntry()
{
}

void startScene::sceneExit()
{
}

void startScene::sceneEnd()
{
	DebugMsg::out("EXITING DEFAULT SCENE\n");
	SoundManager::stopSound("TitleSong");
	inputable::submitInputableDeregistration(AZUL_KEY::KEY_ENTER, INPUT_TYPE::RELEASE);
	img->sceneExit();
}