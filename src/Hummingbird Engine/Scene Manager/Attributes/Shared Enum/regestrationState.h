#ifndef _registrationState
#define _registrationState

///-------------------------------------------------------------------------------------------------
/// <summary>	Values that represent registration states. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
///-------------------------------------------------------------------------------------------------
enum class registrationState
{
	currently_deregistered,
	pending_registration,
	currently_registered,
	pending_deregistration,
};

#endif // !_registrationState