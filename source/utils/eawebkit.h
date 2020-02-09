
#ifndef _UTILS_EAWEBKIT_HEADER
#define _UTILS_EAWEBKIT_HEADER

// Include
#include <string>

// utils
namespace utils {
	
	struct EAWebKitConfig {
		bool supportsLinkHref = false;
		bool supportsScriptSrc = false;
		bool supportsImgSrc = false;
		bool supportImageUrlInCss = false;
		bool supportFontUrlInCss = false;

		EAWebKitConfig() {}
		EAWebKitConfig(bool val){
			supportsLinkHref = val;
			supportsScriptSrc = val;
			supportsImgSrc = val;
			supportImageUrlInCss = val;
			supportFontUrlInCss = val;
		}
		EAWebKitConfig(bool _supportsLinkHref, bool _supportsScriptSrc, bool _supportsImgSrc, bool _supportImageUrlInCss, bool _supportFontUrlInCss) {
			supportsLinkHref = _supportsLinkHref;
			supportsScriptSrc = _supportsScriptSrc;
			supportsImgSrc = _supportsImgSrc;
			supportImageUrlInCss = _supportImageUrlInCss;
			supportFontUrlInCss = _supportFontUrlInCss;
		}
	};

	class EAWebKit {
		private:
			static void replaceUrlPathWithBase64(std::string& file_data, const std::string& extension, const std::string& base64Prefix, 
												 const std::string& contentsFolder);
		public:
			static std::string loadHtml(std::string contentsFolder, std::string file, EAWebKitConfig config);
	};
}

#endif
