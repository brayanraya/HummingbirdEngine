#ifndef _collideableUpdateGroupCommand
#define _collideableUpdateGroupCommand

//#include "collideableCommandBase.h"
#include "collideableGroup.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A collideable deregistraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C">	Type of the c. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C>
class collideableUpdateGroupCommand : public commandBase
{
public:
	collideableUpdateGroupCommand() = delete;
	~collideableUpdateGroupCommand() = default;
	collideableUpdateGroupCommand(C * up) : collideablePointer(up)
	{};
	collideableUpdateGroupCommand(const collideableUpdateGroupCommand& other) = delete;
	collideableUpdateGroupCommand& operator=(const collideableUpdateGroupCommand&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void execute() override;
private:
	C* collideablePointer;
};

template<typename C>
inline void collideableUpdateGroupCommand<C>::execute()
{
	collideableGroup<C>::update();
}

#endif