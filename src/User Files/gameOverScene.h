#pragma once

#include "../Hummingbird Engine/Scene Manager/Scene/scene.h"
class gameOverScene : public scene, public inputable
{
public:
	gameOverScene();
	~gameOverScene();
	virtual void sceneEnd();
	virtual void initialize();
	virtual void keyPress(AZUL_KEY k);
	virtual void keyRelease(AZUL_KEY k);
	virtual void sceneEntry();
	virtual void sceneExit();
private:
};