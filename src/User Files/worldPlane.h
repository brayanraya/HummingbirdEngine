#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"
#include "Align16.h"

class frigate;

class worldPlane: public drawable, public alarmable, public collideable, public Align16
{
public:
	worldPlane();
	~worldPlane();

	void sceneEntry();
	void sceneExit();
	virtual void draw() override;
	void darkness();
	void lightness();
	//virtual void alarm0() override;
	//virtual void alarm1() override;


private:
	GraphicsObject_TextureFlat *pGObj_Plane;
	bool checkForReg = false;
};

