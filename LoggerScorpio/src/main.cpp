#include "Log.h"


// Class test

int main()
{
	Log::Init();
	// w przypadku bezsensownej nazwy pokroju "dawdawdawdg" logger zostanie wy³¹czony,
	// ale w³¹czy go ponownie kolejne poprawne ustawienie poziomu
	Log::LogSetLevel("adawdawdawd");
	Log::LogSetLevel("trace"); // z ma³ych!
	LOG_TRACE("Hello world");
	int errorVal = 13;
	LOG_INFO("Everything is {1} {0}", "so far", "fine");
	LOG_ERROR("Error, the val is {}", errorVal);
	LOG_CRITICAL("The system is about to dump");
	LOG_CRITICAL(false);
	ERR_ERROR("Just a test {}", "of padding values");
}