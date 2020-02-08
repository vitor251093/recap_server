
// Include
#include "eawebkit.h"
#include "base64.h"
#include "functions.h"
#include "../game/config.h"

// utils
namespace utils {

	// Web
	std::string EAWebKit::loadHtml(std::string contentsFolder, std::string file, EAWebKitConfig config) {
		std::string file_data = utils::get_file_text(contentsFolder + file);

		size_t pos = 0;
		std::string tag;
		std::string tagUrl;

		if (!config.supportsLinkHref) {
			std::string cssLinkOpenTag = "<link rel=\"stylesheet\" type=\"text/css\" href=\"";
			std::string cssLinkCloseTag = "\">";
			while ((pos = file_data.find(cssLinkOpenTag)) != std::string::npos) {
				tag = file_data.substr(pos, file_data.find(cssLinkCloseTag, pos) + cssLinkCloseTag.length() - pos);
				tagUrl = tag.substr(cssLinkOpenTag.length(), tag.length() - cssLinkOpenTag.length() - cssLinkCloseTag.length());
				std::string cssPath = contentsFolder + tagUrl;
				std::string cssContents = utils::get_file_text(cssPath);
				utils::string_replace(file_data, tag, "<style type=\"text/css\">\n" + cssContents + "\n</style>");
			}
		}

		if (!config.supportsScriptSrc) {
			std::string jsScriptOpenTag = "<script type=\"text/javascript\" src=\"";
			std::string jsScriptCloseTag = "\"></script>";
			while ((pos = file_data.find(jsScriptOpenTag)) != std::string::npos) {
				tag = file_data.substr(pos, file_data.find(jsScriptCloseTag, pos) + jsScriptCloseTag.length() - pos);
				tagUrl = tag.substr(jsScriptOpenTag.length(), tag.length() - jsScriptOpenTag.length() - jsScriptCloseTag.length());
				std::string jQueryPath = contentsFolder + tagUrl;
				std::string jQueryContents = utils::get_file_text(jQueryPath);
				utils::string_replace(file_data, tag, "<script type=\"text/javascript\">\n" + jQueryContents + "\n</script>");
			}
		}

		if (!config.supportsImgSrc) {
			std::string imgOpenTag = "<img src=\"";
			std::string imgCloseTag = "\"";
			while ((pos = file_data.find(imgOpenTag)) != std::string::npos) {
				tag = file_data.substr(pos, file_data.find(imgCloseTag, pos) + imgCloseTag.length() - pos);
				tagUrl = tag.substr(imgOpenTag.length(), tag.length() - imgOpenTag.length() - imgCloseTag.length());
				std::string extension = tagUrl.substr(tagUrl.find_last_of(".") + 1);
				std::string imgPath = contentsFolder + tagUrl;
				std::string imgBase64Contents = base64_encode(utils::get_file_text(imgPath));
				utils::string_replace(file_data, tag, "<img src=\"data:image/" + extension + ";base," + imgBase64Contents + "\"");
			}
		}

		utils::string_replace(file_data, "{{isDev}}", "true");
		utils::string_replace(file_data, "{{recap-version}}", Game::Config::recapVersion());
		utils::string_replace(file_data, "{{host}}", Game::Config::Get(Game::CONFIG_SERVER_HOST));
		utils::string_replace(file_data, "{{game-mode}}", Game::Config::GetBool(Game::CONFIG_SINGLEPLAYER_ONLY) ? "singleplayer" : "multiplayer");

		return file_data;
	}
}
