#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"

class frigate;

class ground: public drawable
{
public:
	ground();
	~ground();

	void sceneEntry();
	void sceneExit();
	virtual void draw() override;

private:
	GraphicsObject_TextureFlat *pGObj_Plane;
};

