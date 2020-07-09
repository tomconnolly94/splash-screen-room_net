#include "SplashScreenRoomNetUtil.h"
bool SplashScreenRoomNetUtil::FileExists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string SplashScreenRoomNetUtil::GetExtension(std::string input, bool greedy) 
// greedy = true means treat the extension as only the chars right of the last "." e.g. "jquery.js.map" => "map". (greedy = false produces ".js.map")
{
	std::string delimiter = ".";
	size_t pos = 0;
	size_t prevPos = 0;

	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		prevPos = pos;
		input.erase(0, pos + delimiter.length());

		if (!greedy)
		{
			return input;
		}
	}
	return input;
}