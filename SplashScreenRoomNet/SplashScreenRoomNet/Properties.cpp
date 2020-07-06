//external includes


//internal includes
#include "Properties.h"

void Properties::Configure()
{
	directoryMappings = {
		{ DIRECTORY::htmlDir, "web/html"},
		{ DIRECTORY::cssDir, "web/css"},
		{ DIRECTORY::jsDir, "web/js"},
		{ DIRECTORY::imagesDir, "web/images"},
		{ DIRECTORY::nodeModulesDir, "web/node_modules"},
	};

	contentTypeMappings = {
		{ CONTENT_TYPE::textHtml, "text/html"},
		{ CONTENT_TYPE::textCss, "text/css"},
		{ CONTENT_TYPE::appJs, "application/javascript"},
		{ CONTENT_TYPE::imagePng, "image/png"},
		{ CONTENT_TYPE::imageIcon, "image/icon"},
		{ CONTENT_TYPE::plaintext, "text/plain"},
	};

	contentTypeDirectoryMappings = {
		{ CONTENT_TYPE::textHtml, DIRECTORY::htmlDir },
		{ CONTENT_TYPE::textCss, DIRECTORY::cssDir },
		{ CONTENT_TYPE::appJs, DIRECTORY::jsDir },
		{ CONTENT_TYPE::imagePng, DIRECTORY::imagesDir },
		{ CONTENT_TYPE::imageIcon, DIRECTORY::imagesDir },
	};

	extensionContentTypeMappings = {
		{ "html", CONTENT_TYPE::textHtml },
		{ "css", CONTENT_TYPE::textCss },
		{ "js", CONTENT_TYPE::appJs },
		{ "png", CONTENT_TYPE::imagePng },
		{ "ico", CONTENT_TYPE::imageIcon },
	};
}