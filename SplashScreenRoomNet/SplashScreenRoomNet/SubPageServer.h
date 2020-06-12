#pragma once

//external includes
#include <map>

//internal includes
#include "PageServer.h"

class SubPageServer {
public:
	static void ConfigureShared();

	enum class CONTENT_TYPE
	{
		textHtml,
		textCss,
		appJs,
		imagePng,
		imageIcon
	};

protected:

	enum class PAGE 
	{
		index,
		error
	};

	enum class DIRECTORY
	{
		htmlDir,
		cssDir,
		jsDir,
		imagesDir,
		nodeModulesDir
	};

	static std::map<DIRECTORY, std::string> directoryMappings;
	static std::map<CONTENT_TYPE, std::string> contentTypeMappings;
	static std::map<CONTENT_TYPE, DIRECTORY> contentTypeDirectoryMappings;
};