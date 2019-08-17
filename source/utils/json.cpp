
// Include
#include "json.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

// utils
namespace utils {

    void json::Set(rapidjson::Document& node, const std::string& label, rapidjson::Value& value) {
        node.AddMember(rapidjson::Value{}.SetString(label.c_str(), label.length(), node.GetAllocator()),
					   value, node.GetAllocator());
    }
    void json::Set(rapidjson::Document& node, const std::string& label, const std::string& value) {
		json::Set(node, label, rapidjson::Value{}.SetString(value.c_str(), value.length(), node.GetAllocator()));
	}
	
    
    void json::Set(rapidjson::Value& node, const std::string& label, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
        node.AddMember(rapidjson::Value{}.SetString(label.c_str(), label.length(), allocator),
					   value, allocator);
    }
    void json::Set(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetString(value.c_str(), value.length(), allocator), allocator);
	}


	std::string json::ToString(const rapidjson::Document& document) {
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		return buffer.GetString();
	}


    rapidjson::Value json::NewArray() {
        rapidjson::Value value(rapidjson::kArrayType);
        return value;
    }
}
