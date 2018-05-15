#ifndef _drawableRegistratonCommand
#define _drawableRegistratonCommand

#include "../Command/commandBase.h"
class drawable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A drawable registraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class drawableRegistratonCommand: public commandBase
{
public:
	drawableRegistratonCommand() = delete;
	~drawableRegistratonCommand();
	drawableRegistratonCommand(const drawableRegistratonCommand& other) = default;
	drawableRegistratonCommand& operator=(const drawableRegistratonCommand&) = delete;

	drawableRegistratonCommand(drawable * up);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void execute();
private:
	drawable* drawablePointer;
};

#endif //!_drawableRegistratonCommand