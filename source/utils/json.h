
#ifndef _JSON_FUNCTIONS_HEADER
#define _JSON_FUNCTIONS_HEADER

// Include
#include <cstdint>
#include <vector>
#include <string>
#include <pugixml.hpp>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

// utils
namespace utils {

    class json {
        
		public:
			void SetString(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator);

            std::string ToString(const rapidjson::Document& document);
	};
}

#endif
