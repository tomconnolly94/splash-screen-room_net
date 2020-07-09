//external includes


//internal includes
#include "Properties.h"

//initialise private static members
std::map<Properties::DIRECTORY, std::string> Properties::directoryMappings = {
	{ DIRECTORY::htmlDir, "web/html/"},
	{ DIRECTORY::cssDir, "web/css/"},
	{ DIRECTORY::jsDir, "web/js/"},
	{ DIRECTORY::imagesDir, "web/images/"},
	{ DIRECTORY::nodeModulesDir, "web/node_modules/"},
};

std::map<Properties::CONTENT_TYPE, std::string> Properties::contentTypeMappings = {
		{ CONTENT_TYPE::textHtml, "text/html"},
		{ CONTENT_TYPE::textCss, "text/css"},
		{ CONTENT_TYPE::appJs, "application/javascript"},
		{ CONTENT_TYPE::imagePng, "image/png"},
		{ CONTENT_TYPE::imageIcon, "image/icon"},
		{ CONTENT_TYPE::plaintext, "text/plain"},
};

std::map<Properties::CONTENT_TYPE, Properties::DIRECTORY> Properties::contentTypeDirectoryMappings = {
		{ CONTENT_TYPE::textHtml, DIRECTORY::htmlDir },
		{ CONTENT_TYPE::textCss, DIRECTORY::cssDir },
		{ CONTENT_TYPE::appJs, DIRECTORY::jsDir },
		{ CONTENT_TYPE::imagePng, DIRECTORY::imagesDir },
		{ CONTENT_TYPE::imageIcon, DIRECTORY::imagesDir },
};

std::map<std::string, Properties::CONTENT_TYPE> Properties::extensionContentTypeMappings = {
	{ "html", CONTENT_TYPE::textHtml },
	{ "css", CONTENT_TYPE::textCss },
	{ "js", CONTENT_TYPE::appJs },
	{ "png", CONTENT_TYPE::imagePng },
	{ "ico", CONTENT_TYPE::imageIcon },
};
