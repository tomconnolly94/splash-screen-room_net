//external includes
#include <string>

//internal includes
#include "../../cppcommontproj/CppCommonTProj/Util.h"

class SplashScreenRoomNetUtil : Util
{
public:
	static bool FileExists(const std::string& name);
	static std::string GetExtension(const std::string input);
};