#ifndef _bullet
#define _bullet

#include "AzulCore.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Inputable/inputable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"

#include <list>
class EnemySoldier;

class bullet: public updateable, public drawable, public alarmable, public collideable
{
public:
	bullet();
	~bullet();

	virtual void sceneEntry() override;
	virtual void sceneExit()override;
	void fromFactory(const Vect& inPos, const Matrix& inRot);
	virtual void update()override;
	virtual void draw()override;
	virtual void alarm0()override;
	void collision(EnemySoldier*);

	std::list<bullet*>::iterator quickRemovePos;
private:
	GraphicsObject_WireframeConstantColor *pGObj_BSphere;
	Matrix myScale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix myRotation;
	Vect myPostion;
	const float bulletSpeed = 5;
	bool checkForAlarm;
};

#endif // !_bullet