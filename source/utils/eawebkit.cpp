
// Include
#include "eawebkit.h"
#include "base64.h"
#include "functions.h"
#include "../game/config.h"
#include "logger.h"

// utils
namespace utils {

	void EAWebKit::replaceUrlPathWithBase64(std::string& file_data, const std::string& extension, const std::string& base64Prefix, 
											const std::string& contentsFolder) {
		size_t pos = 0;
		size_t closePos = 0;
		size_t skipLinePos = 0;
		size_t ignorablePos = 0;

		std::string tag;
		std::string tagUrl;
		
		std::string imgOpenTag = "url(\"";
		std::string imgCloseTag = "." + extension + "\")";
		while ((pos = file_data.find(imgOpenTag, ignorablePos)) != std::string::npos) {
			closePos = file_data.find(imgCloseTag, pos + imgOpenTag.length());
			skipLinePos = file_data.find("\n", pos + imgOpenTag.length());
			if (skipLinePos != std::string::npos && skipLinePos < closePos) {
				ignorablePos = skipLinePos;
				continue;
			}

			tag = file_data.substr(pos, closePos + imgCloseTag.length() - pos);
			tagUrl = tag.substr(imgOpenTag.length(), tag.length() - imgOpenTag.length() - imgCloseTag.length());
			tagUrl = tagUrl + "." + extension;
			std::string folder = (tagUrl.starts_with("/") ? (Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "www") : contentsFolder);
			std::string imgPath = folder + tagUrl;
			std::string imgBase64Contents = base64_encode(utils::get_file_text(imgPath));
			utils::string_replace(file_data, tag, "url(" + base64Prefix + ";base64," + imgBase64Contents + ")");
		}
	}

	std::string EAWebKit::loadHtml(std::string contentsFolder, std::string file, EAWebKitConfig config) {
		std::string file_data = utils::get_file_text(contentsFolder + file);

		size_t pos = 0;
		std::string tag;
		std::string tagUrl;

		if (!config.supportsLinkHref) {
			std::string cssLinkOpenTag = "<link rel=\"stylesheet\" type=\"text/css\" href=\"";
			std::string cssLinkCloseTag = "\">";
			while ((pos = file_data.find(cssLinkOpenTag)) != std::string::npos) {
				tag = file_data.substr(pos, file_data.find(cssLinkCloseTag, pos + cssLinkOpenTag.length()) + cssLinkCloseTag.length() - pos);
				tagUrl = tag.substr(cssLinkOpenTag.length(), tag.length() - cssLinkOpenTag.length() - cssLinkCloseTag.length());
				std::string folder = (tagUrl.starts_with("/") ? (Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "www") : contentsFolder);
				std::string cssPath = folder + tagUrl;
				std::string cssContents = utils::get_file_text(cssPath);
				utils::string_replace(file_data, tag, "<style type=\"text/css\">\n" + cssContents + "\n</style>");
			}
		}

		if (!config.supportsScriptSrc) {
			std::string jsScriptOpenTag = "<script type=\"text/javascript\" src=\"";
			std::string jsScriptCloseTag = "\"></script>";
			while ((pos = file_data.find(jsScriptOpenTag)) != std::string::npos) {
				tag = file_data.substr(pos, file_data.find(jsScriptCloseTag, pos + jsScriptOpenTag.length()) + jsScriptCloseTag.length() - pos);
				tagUrl = tag.substr(jsScriptOpenTag.length(), tag.length() - jsScriptOpenTag.length() - jsScriptCloseTag.length());
				std::string folder = (tagUrl.starts_with("/") ? (Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "www") : contentsFolder);
				std::string jQueryPath = folder + tagUrl;
				std::string jQueryContents = utils::get_file_text(jQueryPath);
				utils::string_replace(file_data, tag, "<script type=\"text/javascript\">\n" + jQueryContents + "\n</script>");
			}
		}

		if (!config.supportsImgSrc) {
			std::string imgOpenTag = "<img src=\"";
			std::string imgCloseTag = "\"";
			while ((pos = file_data.find(imgOpenTag)) != std::string::npos) {
				tag = file_data.substr(pos, file_data.find(imgCloseTag, pos + imgOpenTag.length()) + imgCloseTag.length() - pos);
				tagUrl = tag.substr(imgOpenTag.length(), tag.length() - imgOpenTag.length() - imgCloseTag.length());
				size_t extensionPoint = tagUrl.find_last_of(".");
				std::string extension = tagUrl.substr(extensionPoint + 1, tagUrl.size() - extensionPoint - 1);
				std::string folder = (tagUrl.starts_with("/") ? (Game::Config::Get(Game::CONFIG_STORAGE_PATH) + "www") : contentsFolder);
				std::string imgPath = folder + tagUrl;
				std::string imgBase64Contents = base64_encode(utils::get_file_text(imgPath));
				utils::string_replace(file_data, tag, "<img loaded src=\"data:image/" + extension + ";base64," + imgBase64Contents + "\"");
			}
		}

		if (!config.supportImageUrlInCss) {
			std::vector<std::string> compatibleImageExtensions = { "png", "jpg", "bmp" };
			for (const std::string& extension : compatibleImageExtensions) {
				replaceUrlPathWithBase64(file_data, extension, "data:image/" + extension, contentsFolder);
			}
		}

		if (!config.supportFontUrlInCss) {
			std::vector<std::string> compatibleFontExtensions = { "ttf" };
			for (const std::string& extension : compatibleFontExtensions) {
				replaceUrlPathWithBase64(file_data, extension, "data:font/truetype;charset=utf-8", contentsFolder);
			}
		}

		utils::string_replace(file_data, "{{isDev}}", "true");
		utils::string_replace(file_data, "{{recap-version}}", Game::Config::recapVersion());
		utils::string_replace(file_data, "{{host}}", Game::Config::Get(Game::CONFIG_SERVER_HOST));
		utils::string_replace(file_data, "{{game-mode}}", Game::Config::GetBool(Game::CONFIG_SINGLEPLAYER_ONLY) ? "singleplayer" : "multiplayer");

		return file_data;
	}
}
