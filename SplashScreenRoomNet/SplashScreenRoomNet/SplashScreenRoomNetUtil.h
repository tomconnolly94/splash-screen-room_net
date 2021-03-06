#pragma once
//external includes
#include <string>
#include <vector>

//internal includes
#include "../../cppcommontproj/CppCommonTProj/Util.h"

class SplashScreenRoomNetUtil : Util
{
public:
	static bool FileExists(const std::string& name);
	static std::string GetExtension(const std::string input, bool greedy = true);
};
