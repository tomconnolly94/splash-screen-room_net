#include "SplashScreenRoomNetUtil.h"

bool SplashScreenRoomNetUtil::FileExists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}