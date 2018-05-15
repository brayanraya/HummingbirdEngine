#ifndef _TankShell
#define _TankShell

#include "AzulCore.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Inputable/inputable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"

#include <list>
class EnemySoldier;

class TankShell: public updateable, public drawable, public alarmable, public collideable
{
public:
	TankShell();
	~TankShell();

	virtual void sceneEntry() override;
	virtual void sceneExit()override;
	void fromFactory(const Vect& inPos, const Matrix& inRot);
	virtual void update()override;
	virtual void draw()override;
	virtual void alarm0()override;
	virtual void alarm1() override;
	void collision(EnemySoldier*);

	std::list<TankShell*>::iterator quickRemovePos;
private:
	GraphicsObject_WireframeConstantColor *pGObj_BSphere;
	float scaleFactor  = 1.0f;
	Matrix myRotation;
	Vect myPostion;
	const float TankShellSpeed = 2;
	bool checkForAlarm;
	bool checkForAlarm2;
};

#endif // !_TankShell