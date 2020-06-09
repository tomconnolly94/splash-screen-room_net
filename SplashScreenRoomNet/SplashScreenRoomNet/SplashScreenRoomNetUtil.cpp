#include "SplashScreenRoomNetUtil.h"

bool SplashScreenRoomNetUtil::FileExists(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string SplashScreenRoomNetUtil::GetExtension(std::string input)
{
	std::string delimiter = ".";
	size_t pos = 0;
	size_t prevPos = 0;

	while ((pos = input.find(delimiter)) != std::string::npos)
	{
		prevPos = pos;
		input.erase(0, pos + delimiter.length());
	}
	return input;
}