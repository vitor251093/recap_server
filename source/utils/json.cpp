
// Include
#include "json.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

// utils
namespace utils {

	void json::SetString(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator) {
		node.AddMember(rapidjson::Value{}.SetString(label.c_str(), label.length(), allocator),
					   rapidjson::Value{}.SetString(value.c_str(), value.length(), allocator), 
					   allocator);
	}

	std::string json::ToString(const rapidjson::Document& document) {
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		return buffer.GetString();
	}
}
