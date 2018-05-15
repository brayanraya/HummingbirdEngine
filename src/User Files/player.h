#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

#include <list>

class frigate;
class EnemyBullet;
class tank;

class player: public drawable, public updateable, public alarmable, public collideable,public inputable
{
public:
	player();
	~player();

	void sceneEntry();
	void sceneExit();
	virtual void draw() override;
	virtual void update() override;
	virtual void keyPress(AZUL_KEY k) override;
	virtual void keyRelease(AZUL_KEY k) override;
	void outOfRadius(const Vect& inVec);
	virtual void alarm0()override;
	void inTankPos(const Vect & inMat);
	void collision(EnemyBullet*);
	void collision(tank *);
	void TerrainCollision()override;

	const Vect getPos() const;
private:
	GraphicsObject_TextureLight *pplayer;
	Matrix world;
	Matrix myScale;
	Matrix myRotation;
	Vect myPosition;
	const float TransSpeed = 1.7f;
	const float ShipRotAng = .0125f;
	float health;
	int numberShot = 0;
	bool active;
};

