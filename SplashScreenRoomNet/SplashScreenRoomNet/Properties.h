#pragma once

//external includes
#include <map>
#include <string>

static class Properties {
public:
	static enum class CONTENT_TYPE
	{
		textHtml,
		textCss,
		appJs,
		imagePng,
		imageIcon,
		plaintext,
		appOctetStream
	};

	static enum class PAGE
	{
		index,
		error
	};

	static enum class DIRECTORY
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
	static std::map<std::string, CONTENT_TYPE> extensionContentTypeMappings;
};
