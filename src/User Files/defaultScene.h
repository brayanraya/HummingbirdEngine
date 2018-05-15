#pragma once

#include "../Hummingbird Engine/Scene Manager/Scene/scene.h"

class startHUD;

class startScene : public scene, public inputable
{
public:
	startScene();
	~startScene();
	virtual void sceneEnd();
	virtual void initialize();
	virtual void keyPress(AZUL_KEY k);
	virtual void keyRelease(AZUL_KEY k);
	virtual void sceneEntry();
	virtual void sceneExit();

private:
	startHUD * img;
};