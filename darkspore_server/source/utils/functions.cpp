
// Include
#include "functions.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <array>
#include <cctype>

// utils
namespace utils {
	// Time
	uint64_t get_unix_time() {
		return std::chrono::milliseconds(std::time(nullptr)).count();
	}

	uint64_t get_milliseconds() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}

	std::string get_utc_date_string() {
		thread_local std::array<char, 256> date;

		auto t = std::time(nullptr);
		auto gmt = std::gmtime(&t);
		auto len = std::strftime(date.data(), date.size(), "%a, %d %b %Y %H:%M:%S %Z", gmt);

		return std::string(date.data(), len);
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

	// Strings
	bool string_iequals(const std::string& lhs, const std::string& rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](char a, char b) {
			return const_tolower(a) == const_tolower(b);
		});
	}

	bool string_iequals(std::string_view lhs, std::string_view rhs) {
		return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), [](char a, char b) {
			return const_tolower(a) == const_tolower(b);
		});
	}

	bool string_iequals(const char* lhs, const char* rhs) {
		return string_iequals(std::string_view(lhs), std::string_view(rhs));
	}

	std::string string_tolower(std::string_view str) {
		std::string result(str);
		std::transform(result.begin(), result.end(), result.begin(),
					   [](unsigned char c) { return std::tolower(c); });
		return result;
	}

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

	// random
	thread_local std::mt19937 random::sGenerator;
}
