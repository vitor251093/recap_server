
// Include
#include "json.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

// utils
namespace utils {

    rapidjson::Document json::Parse(const std::string& contents) {
        rapidjson::Document userJson;
		userJson.Parse(contents);
        return userJson;
    }
    rapidjson::Document json::NewDocumentObject() {
        rapidjson::Document document;
		document.SetObject();
        return document;
    }


    rapidjson::Value json::NewObject() {
        rapidjson::Value value(rapidjson::kObjectType);
        return value;
    }
    rapidjson::Value json::NewArray() {
        rapidjson::Value value(rapidjson::kArrayType);
        return value;
    }




    void json::Set(rapidjson::Document& node, const std::string& label, rapidjson::Value& value) {
        node.AddMember(rapidjson::Value{}.SetString(label.c_str(), label.length(), node.GetAllocator()), value, node.GetAllocator());
    }
    void json::Set(rapidjson::Document& node, const std::string& label, const std::string& value) {
		json::Set(node, label, rapidjson::Value{}.SetString(value.c_str(), value.length(), node.GetAllocator()));
	}
    void json::Set(rapidjson::Document& node, const std::string& label, bool value) {
		json::Set(node, label, rapidjson::Value{}.SetBool(value));
	}
    void json::Set(rapidjson::Document& node, const std::string& label, double value) {
		json::Set(node, label, rapidjson::Value{}.SetDouble(value));
	}
    void json::Set(rapidjson::Document& node, const std::string& label, uint32_t value) {
		json::Set(node, label, rapidjson::Value{}.SetUint(value));
	}
    void json::Set(rapidjson::Document& node, const std::string& label, uint64_t value) {
		json::Set(node, label, rapidjson::Value{}.SetUint64(value));
	}
    
    
    void json::Add(rapidjson::Document& node, rapidjson::Value& value) {
        node.PushBack(value, node.GetAllocator());
    }
    void json::Add(rapidjson::Document& node, const std::string& value) {
		json::Add(node, rapidjson::Value{}.SetString(value.c_str(), value.length(), node.GetAllocator()));
	}


	
    
    void json::Set(rapidjson::Value& node, const std::string& label, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
        node.AddMember(rapidjson::Value{}.SetString(label.c_str(), label.length(), allocator), value, allocator);
    }
    void json::Set(rapidjson::Value& node, const std::string& label, const std::string& value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetString(value.c_str(), value.length(), allocator), allocator);
	}
    void json::Set(rapidjson::Value& node, const std::string& label, bool value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetBool(value), allocator);
	}
    void json::Set(rapidjson::Value& node, const std::string& label, double value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetDouble(value), allocator);
	}
    void json::Set(rapidjson::Value& node, const std::string& label, uint32_t value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetUint(value), allocator);
	}
    void json::Set(rapidjson::Value& node, const std::string& label, uint64_t value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetUint64(value), allocator);
	}
    
    
    void json::Add(rapidjson::Value& node, rapidjson::Value& value, rapidjson::Document::AllocatorType& allocator) {
        node.PushBack(value, allocator);
    }
    void json::Add(rapidjson::Value& node, const std::string& value, rapidjson::Document::AllocatorType& allocator) {
		json::Add(node, rapidjson::Value{}.SetString(value.c_str(), value.length(), allocator), allocator);
	}




	std::string json::ToString(const rapidjson::Document& document) {
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		return buffer.GetString();
	}
}
