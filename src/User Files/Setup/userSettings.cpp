#include "../src/Hummingbird Engine/Main Game/hummingbirdEngine.h"

#include "hummingbirdCore.h"
void hummingbirdEngine::LoadUserSettings()
{
	/// Use this area, for one time non-graphic creation
	/// Game Window Device setup REQURIED
	setWindowName("Hummingbird Engine");
	setWidthHeight(1147, 631); // 
	setClearColor(Color::SlateGray);
}