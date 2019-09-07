
#ifndef _XML_FUNCTIONS_HEADER
#define _XML_FUNCTIONS_HEADER

// Include
#include <cstdint>
#include <vector>
#include <string>
#include <pugixml.hpp>

// utils
namespace utils {
    namespace xml {
        void Set(pugi::xml_node& node, const std::string& name, const std::string& value);
        std::string GetString(const pugi::xml_node& node, const std::string& name);

        template<typename T>
        std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, void> Set(pugi::xml_node& node, const std::string& name, T value) {
            Set(node, name, std::to_string(value));
        }

        template<typename T>
        std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, T> GetString(const pugi::xml_node& node, const std::string& name) {
            return to_number<T>(GetString(node, name));
        }

        std::string ToString(pugi::xml_document& document);
    }
}

#endif
