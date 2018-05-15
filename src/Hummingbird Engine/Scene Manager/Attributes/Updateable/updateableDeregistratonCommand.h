#ifndef _updateableDeregistratonCommand
#define _updateableDeregistratonCommand

#include "../Command/commandBase.h"

class updateable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An updateable deregistraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class updateableDeregistratonCommand: public commandBase
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	updateableDeregistratonCommand() = delete;
	updateableDeregistratonCommand(updateable * up);
	~updateableDeregistratonCommand() = default;
	updateableDeregistratonCommand(const updateableDeregistratonCommand& other) = default;
	updateableDeregistratonCommand& operator=(const updateableDeregistratonCommand&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///--------------------------------------------------------------------------------------------------
	void execute();
private:
	updateable* updateablePointer;
};

#endif //!_updateableDeregistratonCommand