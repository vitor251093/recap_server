
#ifndef _UTILS_FUNCTIONS_HEADER
#define _UTILS_FUNCTIONS_HEADER

// Include
#include <cstdint>
#include <vector>
#include <string>
#include <pugixml.hpp>
#include "json.h"
#include "xml.h"

// utils
namespace utils {
	namespace detail {
		// Strings
		template<class StrT, class DelimT, class StrRT = std::remove_cvref_t<StrT>>
		auto explode_string(StrT str, DelimT delim, int32_t limit) {
			std::vector<StrRT> strings;

			size_t start = 0, end = 0;
			while (--limit != -1 && (end = str.find(delim, start)) != StrRT::npos) {
				strings.push_back(str.substr(start, end - start));
				if constexpr (std::is_class_v<std::remove_cvref_t<DelimT>>) {
					start = end + delim.size();
				} else {
					start = end + sizeof(delim);
				}
			}

			strings.push_back(str.substr(start));
			return strings;
		}
	}

	// Other
	constexpr int const_tolower(int c) {
		return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
	}

	// Time
	uint64_t get_unix_time();

	// Files
	std::string get_file_text(const std::string& path);

	// Strings
	void string_replace(std::string& str, const std::string& old_str, const std::string& new_str);

	std::string unsigned_long_long_to_hex_string(uint64_t val);
	uint64_t hex_string_to_unsigned_long_long(std::string str);

	std::vector<std::string> explode_string(const std::string& str, char delim, int32_t limit = -1);
	std::vector<std::string> explode_string(const std::string& str, const std::string& delim, int32_t limit = -1);

	std::vector<std::string_view> explode_string(std::string_view str, char delim, int32_t limit = -1);
	std::vector<std::string_view> explode_string(std::string_view str, std::string_view delim, int32_t limit = -1);

	// Numbers
	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, T> to_number(const std::string& str) {
		return static_cast<T>(tonumber<std::underlying_type_t<T>>(str));
	}

	template<typename T>
	std::enable_if_t<std::is_integral_v<T>, T> to_number(const std::string& str, int base = 10) {
		T value;
		try {
			if constexpr (std::is_signed_v<T>) {
				if constexpr (sizeof(T) >= sizeof(int64_t)) {
					value = std::stoll(str, nullptr, base);
				} else {
					value = static_cast<T>(std::stol(str, nullptr, base));
				}
			}
			else {
				if constexpr (sizeof(T) >= sizeof(uint64_t)) {
					value = std::stoull(str, nullptr, base);
				} else {
					value = static_cast<T>(std::stoul(str, nullptr, base));
				}
			}
		} catch (...) {
			value = static_cast<T>(0);
		}
		return value;
	}

	template<typename T>
	std::enable_if_t<std::is_floating_point_v<T>, T> to_number(const std::string& str) {
		T value;
		try {
			if constexpr (std::is_same_v<T, double>) {
				value = std::stod(str);
			} else if constexpr (std::is_same_v<T, float>) {
				value = std::stof(str);
			} else {
				value = static_cast<T>(0);
			}
		} catch (...) {
			value = static_cast<T>(0);
		}
		return value;
	}

	// Hashes
	constexpr uint32_t hash_id(const char* pStr) {
		uint32_t rez = 0x811C9DC5u;
		while (*pStr) {
			// To avoid compiler warnings
			rez = static_cast<uint32_t>(rez * static_cast<unsigned long long>(0x1000193));
			rez ^= static_cast<uint32_t>(const_tolower(*pStr));
			++pStr;
		}
		return rez;
	}
}

#endif
