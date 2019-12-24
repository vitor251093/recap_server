
#ifndef _UTILS_JSON_HEADER
#define _UTILS_JSON_HEADER

// Include
#include <cstdint>
#include <vector>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>

// utils
namespace utils {
	namespace json {
        rapidjson::Document Parse(const std::string& contents);
        rapidjson::Document NewDocumentObject();
		rapidjson::Document FromFile(const std::string& fileName);
        
        rapidjson::Value Null();
        rapidjson::Value NewObject();
        rapidjson::Value NewArray();

        rapidjson::Value& Get(rapidjson::Document& node, const char* label);
        std::string GetString(rapidjson::Document& node, const char* label);
        bool        GetBool(  rapidjson::Document& node, const char* label);
        double      GetDouble(rapidjson::Document& node, const char* label);
        uint8_t     GetUint8( rapidjson::Document& node, const char* label);
        uint16_t    GetUint16(rapidjson::Document& node, const char* label);
        uint32_t    GetUint(  rapidjson::Document& node, const char* label);
        uint64_t    GetUint64(rapidjson::Document& node, const char* label);
        
        void Set(rapidjson::Document& node, const std::string& label, rapidjson::Value& value);
        void Set(rapidjson::Document& node, const std::string& label, const std::string& value);
        void Set(rapidjson::Document& node, const std::string& label, bool value);
        void Set(rapidjson::Document& node, const std::string& label, double value);
        void Set(rapidjson::Document& node, const std::string& label, uint8_t value);
        void Set(rapidjson::Document& node, const std::string& label, uint16_t value);
        void Set(rapidjson::Document& node, const std::string& label, uint32_t value);
        void Set(rapidjson::Document& node, const std::string& label, uint64_t value);

        void Add(rapidjson::Document& node, rapidjson::Value& value);
        void Add(rapidjson::Document& node, const std::string& value);

        rapidjson::Value& Get(rapidjson::Value& node, const char* label);
        std::string GetString(rapidjson::Value& node, const char* label);
        bool        GetBool(  rapidjson::Value& node, const char* label);
        double      GetDouble(rapidjson::Value& node, const char* label);
        uint8_t     GetUint8( rapidjson::Value& node, const char* label);
        uint16_t    GetUint16(rapidjson::Value& node, const char* label);
        uint32_t    GetUint(  rapidjson::Value& node, const char* label);
        uint64_t    GetUint64(rapidjson::Value& node, const char* label);

        void Set(rapidjson::Value& node, const std::string& label, rapidjson::Value& value,  rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, bool value,               rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, double value,             rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, uint8_t value,            rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, uint16_t value,           rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, uint32_t value,           rapidjson::Document::AllocatorType& allocator);
        void Set(rapidjson::Value& node, const std::string& label, uint64_t value,           rapidjson::Document::AllocatorType& allocator);
        
        void Add(rapidjson::Value& node, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator);
        void Add(rapidjson::Value& node, const std::string& value, rapidjson::Document::AllocatorType& allocator);

	    std::string ToString(const rapidjson::Document& document);
	}
}

#endif
