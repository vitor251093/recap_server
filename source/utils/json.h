
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
        rapidjson::Document Parse(const std::string& contents);
        rapidjson::Document NewDocumentObject();
        
        rapidjson::Value NewObject();
        rapidjson::Value NewArray();

        std::string GetString(rapidjson::Document& node, const rapidjson::ValueType::Ch& label);
        bool        GetBool(  rapidjson::Document& node, const rapidjson::ValueType::Ch& label);
        double      GetDouble(rapidjson::Document& node, const rapidjson::ValueType::Ch& label);
        uint32_t    GetUint(  rapidjson::Document& node, const rapidjson::ValueType::Ch& label);
        uint64_t    GetUint64(rapidjson::Document& node, const rapidjson::ValueType::Ch& label);
        
        void Set(rapidjson::Document& node, const std::string& label, rapidjson::Value& value);
        void Set(rapidjson::Document& node, const std::string& label, const std::string& value);
        void Set(rapidjson::Document& node, const std::string& label, bool value);
        void Set(rapidjson::Document& node, const std::string& label, double value);
        void Set(rapidjson::Document& node, const std::string& label, uint32_t value);
        void Set(rapidjson::Document& node, const std::string& label, uint64_t value);

        void Add(rapidjson::Document& node, rapidjson::Value& value);
        void Add(rapidjson::Document& node, const std::string& value);

        std::string GetString(rapidjson::Value& node, const rapidjson::ValueType::Ch& label);
        bool        GetBool(  rapidjson::Value& node, const rapidjson::ValueType::Ch& label);
        double      GetDouble(rapidjson::Value& node, const rapidjson::ValueType::Ch& label);
        uint32_t    GetUint(  rapidjson::Value& node, const rapidjson::ValueType::Ch& label);
        uint64_t    GetUint64(rapidjson::Value& node, const rapidjson::ValueType::Ch& label);

        void Set(rapidjson::Value& node, const std::string& label, rapidjson::Value& value,  rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, bool value,               rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, double value,             rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, uint32_t value,           rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, uint64_t value,           rapidjson::Document::AllocatorType& allocator);
        
        void Add(rapidjson::Value& node, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator);
        void Add(rapidjson::Value& node, const std::string& value, rapidjson::Document::AllocatorType& allocator);

	    std::string ToString(const rapidjson::Document& document);
	}
}

#endif