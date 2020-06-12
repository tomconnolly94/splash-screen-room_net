//external includes


//internal includes
#include "SubPageServer.h"

void SubPageServer::ConfigureShared()
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
	};



	contentTypeDirectoryMappings = {
		{ CONTENT_TYPE::textHtml, DIRECTORY::htmlDir },
		{ CONTENT_TYPE::textCss, DIRECTORY::cssDir },
		{ CONTENT_TYPE::appJs, DIRECTORY::jsDir },
		{ CONTENT_TYPE::imagePng, DIRECTORY::imagesDir },
		{ CONTENT_TYPE::imageIcon, DIRECTORY::imagesDir },
	};
}