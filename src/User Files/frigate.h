#ifndef _frigate
#define _frigate

#include "AzulCore.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Inputable/inputable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"

class EnemySoldier;
class bullet;
class player;

class frigate: public updateable, public drawable, public inputable, public collideable
{
public:
	frigate();
	frigate(const Vect & inPos);
	~frigate();

	void sceneEntry();
	void sceneExit();
	void sceneEntry1();
	void sceneExit1();
	void update();
	void draw();
	void keyPress(AZUL_KEY k);
	void keyRelease(AZUL_KEY k);
	void collision(bullet* inBullet);
	void collision(player* inCot);



	
private:
	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;
	// Spaceship vars
	Matrix myScale;
	Matrix myRot;
	Vect myPosition;
	Matrix world;
	const float ShipTransSpeed = 1.5f;
	const float ShipRotAng = .025f;
	const float ScaleFactor = 0.5f;
	bool toggleCam = true;
	bool dead;
};

#endif // !_frigate