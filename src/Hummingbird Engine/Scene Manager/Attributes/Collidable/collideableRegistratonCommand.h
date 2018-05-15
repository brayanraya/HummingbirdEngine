#ifndef _collideableRegistratonCommand
#define _collideableRegistratonCommand

#include "collideableCommandBase.h"
#include "collideableGroup.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A collideable registraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C">	Type of the c. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C>
class collideableRegistratonCommand: public collideableCommandBase
{
public:
	collideableRegistratonCommand() = delete;
	~collideableRegistratonCommand() = default;
	collideableRegistratonCommand(C * up) : collideablePointer(up)
	{};
	collideableRegistratonCommand(const collideableRegistratonCommand& other) = delete;
	collideableRegistratonCommand& operator=(const collideableRegistratonCommand&) = delete;

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
inline void collideableRegistratonCommand<C>::execute()
{
	collideableGroup<C>::registerCollideableGroup(collideablePointer);
}
#endif // !_collideableRegistratonCommand