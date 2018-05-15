#ifndef _EnemtBullet
#define _EnemtBullet

#include "AzulCore.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Inputable/inputable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"

#include <list>
class player;
class tank;

class EnemyBullet: public updateable, public drawable, public alarmable, public collideable
{
public:
	EnemyBullet();
	~EnemyBullet();

	virtual void sceneEntry() override;
	virtual void sceneExit()override;
	void fromFactory(const Vect& inPos, const Matrix& inRot);
	virtual void update()override;
	virtual void draw()override;
	virtual void alarm0()override;
	void collision(player*);
	void collision(tank*);


	std::list<EnemyBullet*>::iterator quickRemovePos;
private:
	GraphicsObject_WireframeConstantColor *pGObj_BSphere;
	Matrix myScale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix myRotation;
	Vect myPostion;
	const float EnemtBulletSpeed = 5;
	bool checkForAlarm;
};

#endif // !_EnemtBullet