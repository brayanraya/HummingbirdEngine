#ifndef _collideableDeregistratonCommand
#define _collideableDeregistratonCommand

#include "collideableCommandBase.h"
#include "collideableGroup.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A collideable deregistraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///
/// <typeparam name="C">	Type of the c. </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename C>
class collideableDeregistratonCommand : public collideableCommandBase
{
public:
	collideableDeregistratonCommand() = delete;
	~collideableDeregistratonCommand() = default;
	collideableDeregistratonCommand(C * up) : collideablePointer(up)
	{};
	collideableDeregistratonCommand(const collideableDeregistratonCommand& other) = delete;
	collideableDeregistratonCommand& operator=(const collideableDeregistratonCommand&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void execute();

private:
	C* collideablePointer;
};

template<typename C>
inline void collideableDeregistratonCommand<C>::execute()
{
	collideableGroup<C>::deregisterCollideableGroup(collideablePointer);
	//collideablePointer->freeMemory();
}
#endif // !_collideableDeregistratonCommand