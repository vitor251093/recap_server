
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
		void SetString(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator);
	    std::string ToString(const rapidjson::Document& document);
	}
}

#endif
