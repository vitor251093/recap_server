
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

		EAWebKitConfig() {}
		EAWebKitConfig(bool val){
			supportsLinkHref = val;
			supportsScriptSrc = val;
			supportsImgSrc = val;
		}
		EAWebKitConfig(bool _supportsLinkHref, bool _supportsScriptSrc, bool _supportsImgSrc) {
			supportsLinkHref = _supportsLinkHref;
			supportsScriptSrc = _supportsScriptSrc;
			supportsImgSrc = _supportsImgSrc;
		}
	};

	class EAWebKit {
		public:
			static std::string loadHtml(std::string contentsFolder, std::string file, EAWebKitConfig config);
	};
}

#endif
