
// Include
#include "functions.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

// utils
namespace utils {
	// Time
	uint64_t get_unix_time() {
		return std::chrono::milliseconds(std::time(nullptr)).count();
	}

	// Files
	std::string get_file_text(const std::string& path) {
		std::filesystem::path fspath = path;
		std::ifstream stream(fspath.c_str(), std::ios::binary);
		if (stream.is_open()) {
			stream.seekg(0, std::ios::end);

			std::string str(stream.tellg(), '\0');
			stream.seekg(0, std::ios::beg);

			stream.read(&str[0], str.length());
			return str;
		} else {
			return "File " + path + " does not exist.";
		}
	}

	// Web
	std::string get_html_file_for_darkspore_webkit(std::string path, std::string contentsFolder) {
		std::string file_data = utils::get_file_text(path);
		
		size_t pos = 0;
		std::string tag;
		std::string tagUrl;
		std::string cssLinkOpenTag = "<link rel=\"stylesheet\" type=\"text/css\" href=\"";
		std::string cssLinkCloseTag = "\">";
		while ((pos = file_data.find(cssLinkOpenTag)) != std::string::npos) {
			tag = file_data.substr(pos, file_data.find(cssLinkCloseTag, pos) + cssLinkCloseTag.length() - pos);
			tagUrl = tag.substr(cssLinkOpenTag.length(), tag.length() - cssLinkOpenTag.length() - cssLinkCloseTag.length());
			std::string cssPath = contentsFolder + tagUrl;
			std::string cssContents = utils::get_file_text(cssPath);
			utils::string_replace(file_data, tag, "<style type=\"text/css\">\n" + cssContents + "\n</style>");
		}

		std::string jsScriptOpenTag = "<script type=\"text/javascript\" src=\"";
		std::string jsScriptCloseTag = "\"></script>";
		while ((pos = file_data.find(jsScriptOpenTag)) != std::string::npos) {
			tag = file_data.substr(pos, file_data.find(jsScriptCloseTag, pos) + jsScriptCloseTag.length() - pos);
			tagUrl = tag.substr(jsScriptOpenTag.length(), tag.length() - jsScriptOpenTag.length() - jsScriptCloseTag.length());
			std::string jQueryPath = contentsFolder + tagUrl;
			std::string jQueryContents = utils::get_file_text(jQueryPath);
			utils::string_replace(file_data, tag, "<script type=\"text/javascript\">\n" + jQueryContents + "\n</script>");
		}

		return file_data;
	}

	// Strings
	void string_replace(std::string& str, const std::string& old_str, const std::string& new_str) {
		auto position = str.find(old_str);
		if (position != std::string::npos) {
			str.replace(position, old_str.length(), new_str);
		}
	}

	std::vector<std::string> explode_string(const std::string& str, char delim, int32_t limit) {
		return detail::explode_string<const std::string&, char>(str, delim, limit);
	}

	std::vector<std::string> explode_string(const std::string& str, const std::string& delim, int32_t limit) {
		return detail::explode_string<const std::string&, const std::string&>(str, delim, limit);
	}

	std::vector<std::string_view> explode_string(std::string_view str, char delim, int32_t limit) {
		return detail::explode_string<std::string_view, char>(str, delim, limit);
	}

	std::vector<std::string_view> explode_string(std::string_view str, std::string_view delim, int32_t limit) {
		return detail::explode_string<std::string_view, std::string_view>(str, delim, limit);
	}

	// XML
	void xml_add_text_node(pugi::xml_node& node, const std::string& name, const std::string& value) {
		node.append_child(name.c_str()).append_child(pugi::node_pcdata).set_value(value.c_str());
	}

	std::string xml_get_text_node(const pugi::xml_node& node, const std::string& name) {
		return node.child(name.c_str()).text().get();
	}
}
