#ifndef _updateableRegistratonCommand
#define _updateableRegistratonCommand

#include "../Command/commandBase.h"

class updateable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An updateable registraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class updateableRegistratonCommand: public commandBase
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	updateableRegistratonCommand() = delete;
	updateableRegistratonCommand(updateable * up);
	~updateableRegistratonCommand() = default;
	updateableRegistratonCommand(const updateableRegistratonCommand& other) = default;
	updateableRegistratonCommand& operator=(const updateableRegistratonCommand&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void execute();

private:
	updateable* updateablePointer;
};

#endif _updateableRegistratonCommand
