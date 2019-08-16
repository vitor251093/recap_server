
#ifndef _UTILS_JSON_HEADER
#define _UTILS_JSON_HEADER

// Include
#include <cstdint>
#include <vector>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

// utils
namespace utils {
	namespace json {
        void Set(rapidjson::Document& node, const std::string& label, rapidjson::Value& value);
        void Set(rapidjson::Document& node, const std::string& label, const std::string& value);
        
        void Set(rapidjson::Value& node, const std::string& label, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator);

	    std::string ToString(const rapidjson::Document& document);

        rapidjson::Value NewArray();
        rapidjson::Value NewString(const std::string& label, rapidjson::Document::AllocatorType& allocator);
	}
}

#endif
