
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

		EAWebKitConfig() {}
		EAWebKitConfig(bool val){
			supportsLinkHref = val;
			supportsScriptSrc = val;
			supportsImgSrc = val;
			supportImageUrlInCss = val;
		}
		EAWebKitConfig(bool _supportsLinkHref, bool _supportsScriptSrc, bool _supportsImgSrc, bool _supportImageUrlInCss) {
			supportsLinkHref = _supportsLinkHref;
			supportsScriptSrc = _supportsScriptSrc;
			supportsImgSrc = _supportsImgSrc;
			supportImageUrlInCss = _supportImageUrlInCss;
		}
	};

	class EAWebKit {
		public:
			static std::string loadHtml(std::string contentsFolder, std::string file, EAWebKitConfig config);
	};
}

#endif
