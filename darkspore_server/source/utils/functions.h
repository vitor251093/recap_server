
#ifndef _UTILS_FUNCTIONS_HEADER
#define _UTILS_FUNCTIONS_HEADER

// Include
#include <cstdint>
#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <random>
#include <pugixml.hpp>

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

	// Time & Date
	uint64_t get_unix_time();
	uint64_t get_milliseconds();
	std::string get_utc_date_string();

	// Files
	std::string get_file_text(const std::string& path);

	// Strings
	bool string_iequals(const std::string& lhs, const std::string& rhs);
	bool string_iequals(std::string_view lhs, std::string_view rhs);
	bool string_iequals(const char* lhs, const char* rhs);

	void string_replace(std::string& str, const std::string& old_str, const std::string& new_str);

	std::vector<std::string> explode_string(const std::string& str, char delim, int32_t limit = -1);
	std::vector<std::string> explode_string(const std::string& str, const std::string& delim, int32_t limit = -1);

	std::vector<std::string_view> explode_string(std::string_view str, char delim, int32_t limit = -1);
	std::vector<std::string_view> explode_string(std::string_view str, std::string_view delim, int32_t limit = -1);

	// Numbers
	template<typename T>
	std::enable_if_t<std::is_integral_v<T>, T> to_number(std::string_view str, int base = 10) {
		T value;
		try {
			if constexpr (std::is_same_v<T, bool>) {
				using namespace std::string_view_literals;
				if (string_iequals(str, "true"sv)) {
					value = true;
				} else {
					value = std::strtoul(str.data(), nullptr, base) > 0;
				}
			} else if constexpr (std::is_signed_v<T>) {
				if constexpr (sizeof(T) >= sizeof(int64_t)) {
					value = std::strtoll(str.data(), nullptr, base);
				} else {
					value = static_cast<T>(std::strtol(str.data(), nullptr, base));
				}
			} else if constexpr (sizeof(T) >= sizeof(uint64_t)) {
				value = std::strtoull(str.data(), nullptr, base);
			} else {
				value = static_cast<T>(std::strtoul(str.data(), nullptr, base));
			}
		} catch (...) {
			value = static_cast<T>(0);
		}
		return value;
	}

	template<typename T>
	std::enable_if_t<std::is_integral_v<T>, T> to_number(const std::string& str, int base = 10) {
		std::string_view strView = str;
		return to_number<T>(strView, base);
	}

	template<typename T>
	std::enable_if_t<std::is_floating_point_v<T>, T> to_number(std::string_view str) {
		T value;
		try {
			if constexpr (std::is_same_v<T, double>) {
				value = std::strtod(str.data(), nullptr);
			} else if constexpr (std::is_same_v<T, float>) {
				value = std::strtof(str.data(), nullptr);
			} else {
				value = static_cast<T>(0);
			}
		} catch (...) {
			value = static_cast<T>(0);
		}
		return value;
	}

	template<typename T>
	std::enable_if_t<std::is_floating_point_v<T>, T> to_number(const std::string& str) {
		std::string_view strView = str;
		return to_number<T>(strView);
	}

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, T> to_number(std::string_view str, int base = 10) {
		return static_cast<T>(to_number<std::underlying_type_t<T>>(str, base));
	}

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, T> to_number(const std::string& str, int base = 10) {
		return static_cast<T>(to_number<std::underlying_type_t<T>>(str, base));
	}

	// TODO: move xml & js stuff
	// XML
	void xml_add_text_node(pugi::xml_node& node, const std::string& name, const std::string& value);
	std::string xml_get_text_node(const pugi::xml_node& node, const std::string& name);

	template<typename T, size_t S = sizeof(T)>
	void xml_add_text_node(pugi::xml_node& node, const std::string& name, const std::basic_string_view<T>& value) {
		char buf[512];
		std::memcpy(buf, value.data(), std::min<size_t>(sizeof(buf), S * value.length()));
		node.append_child(name.c_str()).append_child(pugi::node_pcdata).set_value(buf);
	}

	template<typename T>
	std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, void> xml_add_text_node(pugi::xml_node& node, const std::string& name, T value) {
		xml_add_text_node(node, name, std::to_string(value));
	}

	template<typename T>
	std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, T> xml_get_text_node(const pugi::xml_node& node, const std::string& name) {
		return to_number<T>(xml_get_text_node(node, name));
	}

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, void> xml_add_text_node(pugi::xml_node& node, const std::string& name, T value) {
		xml_add_text_node(node, name, std::to_string(static_cast<std::underlying_type_t<T>>(value)));
	}

	template<typename T>
	std::enable_if_t<std::is_enum_v<T>, T> xml_get_text_node(const pugi::xml_node& node, const std::string& name) {
		return static_cast<T>(to_number<std::underlying_type_t<T>>(xml_get_text_node(node, name)));
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

	constexpr uint32_t hash_id(std::string_view pStr) {
		return hash_id(pStr.data());
	}

	// Helpers
	class random {
		public:
			template<typename T> requires std::is_enum_v<T>
			static T get(T min, T max) {
				using Tu = std::underlying_type_t<T>;
				return static_cast<T>(get<Tu>(static_cast<Tu>(min), static_cast<Tu>(max)));
			}

			template<typename T> requires std::is_floating_point_v<T> || std::is_integral_v<T>
			static T get(T min, T max) {
				if constexpr (sizeof(T) == 1) { // for i8, u8, etc
					std::uniform_int_distribution<int16_t> distribution(static_cast<int16_t>(min), static_cast<int16_t>(max));
					return static_cast<T>(distribution(sGenerator));
				} else if constexpr (std::is_floating_point_v<T>) {
					std::uniform_real_distribution<T> distribution(min, max);
					return distribution(sGenerator);
				} else if constexpr (std::is_integral_v<T>) {
					std::uniform_int_distribution<T> distribution(min, max);
					return distribution(sGenerator);
				}
			}

		private:
			static thread_local std::mt19937 sGenerator;
	};

	template<typename T, typename U = std::underlying_type_t<T>> requires std::is_enum_v<T>
	class enum_wrapper {
		using this_type = enum_wrapper<T>;
    
		public:
			constexpr enum_wrapper() noexcept = default;
			constexpr enum_wrapper(T value) noexcept : mValue(value) {}
			constexpr operator T() const noexcept { return mValue; }
		
			constexpr T value() const noexcept { return mValue; }
			constexpr U underlying() const noexcept { return static_cast<U>(mValue); }

			template<typename... Ts>
			constexpr auto band(T value, Ts&&... args) noexcept {
				mValue = static_cast<T>(underlying() & static_cast<U>(value));
				if constexpr (sizeof...(args) > 0) {
					return band(std::forward<Ts>(args)...);
				}
				return *this;
			}

			template<typename... Ts>
			constexpr auto bor(T value, Ts&&... args) noexcept {
				mValue = static_cast<T>(underlying() | static_cast<U>(value));
				if constexpr (sizeof...(args) > 0) {
					return bor(std::forward<Ts>(args)...);
				}
				return *this;
			}
		
			template<typename... Ts>
			constexpr auto bxor(T value, Ts&&... args) noexcept {
				mValue = static_cast<T>(underlying() ^ static_cast<U>(value));
				if constexpr (sizeof...(args) > 0) {
					return bxor(std::forward<Ts>(args)...);
				}
				return *this;
			}

			constexpr auto bnot() noexcept {
				mValue = static_cast<T>(~underlying());
				return *this;
			}
		
			constexpr auto lshift(int sh) noexcept {
				mValue = static_cast<T>(underlying() << sh);
				return *this;
			}
		
			constexpr auto rshift(int sh) noexcept {
				mValue = static_cast<T>(underlying() >> sh);
				return *this;
			}

			template<typename... Ts>
			constexpr bool test(Ts&&... args) const noexcept {
				decltype(auto) value = this_type().bor(std::forward<Ts>(args)...).underlying();
				return (underlying() & value) == value;
			}

			static constexpr T next(T value, U n) noexcept {
				return static_cast<T>(underlying() + n);
			}
		
			friend constexpr this_type operator&(const this_type& lhs, const this_type& rhs) { return this_type(lhs).band(rhs); }
			friend constexpr this_type operator|(const this_type& lhs, const this_type& rhs) { return this_type(lhs).bor(rhs); }
			friend constexpr this_type operator^(const this_type& lhs, const this_type& rhs) { return this_type(lhs).bxor(rhs); }
			friend constexpr this_type operator~(const this_type& value) { return this_type(value).bnot(); }
		
			friend constexpr this_type operator<<(const this_type& value, int sh) { return this_type(value).lshift(sh); }
			friend constexpr this_type operator>>(const this_type& value, int sh) { return this_type(value).rshift(sh); }

			friend constexpr auto operator<=>(const this_type& lhs, const this_type& rhs) { return lhs.underlying() <=> rhs.underlying(); }

		private:
			T mValue { static_cast<T>(0) };
	};

	template<typename T, typename U = std::underlying_type_t<T>> requires std::is_enum_v<T>
	struct enum_helper {
		static constexpr T band(T value) noexcept { return value; }
		static constexpr T bor(T value) noexcept { return value; }
		static constexpr T bxor(T value) noexcept { return value; }

		template<typename... Ts>
		static constexpr T band(T lhs, T rhs, Ts&&... args) noexcept {
			lhs = static_cast<T>(static_cast<U>(lhs) & static_cast<U>(rhs));
			if constexpr (sizeof...(args) == 0) {
				return lhs;
			} else {
				return band(lhs, std::forward<Ts>(args)...);
			}
		}

		template<typename... Ts>
		static constexpr T bor(T lhs, T rhs, Ts&&... args) noexcept {
			lhs = static_cast<T>(static_cast<U>(lhs) | static_cast<U>(rhs));
			if constexpr (sizeof...(args) == 0) {
				return lhs;
			} else {
				return bor(lhs, std::forward<Ts>(args)...);
			}
		}

		template<typename... Ts>
		static constexpr T bxor(T lhs, T rhs, Ts&&... args) noexcept {
			lhs = static_cast<T>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
			if constexpr (sizeof...(args) == 0) {
				return lhs;
			} else {
				return bxor(lhs, std::forward<Ts>(args)...);
			}
		}

		template<typename... Ts>
		static constexpr bool test(T value, Ts&&... args) noexcept {
			if constexpr (sizeof...(args) == 0) {
				return static_cast<U>(value) != 0;
			} else {
				return static_cast<U>(band(value, bor(std::forward<Ts>(args)...))) != 0;
			}
		}

		static constexpr T next(T value, U n) noexcept {
			return static_cast<T>(static_cast<U>(value) + n);
		}
	};
}

#endif
