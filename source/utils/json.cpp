
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
	rapidjson::Document json::FromFile(const std::string& fileName) {
		FILE* pFile = fopen(fileName.c_str(), "rb");
		char buffer[65536];
		rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
		rapidjson::Document document;
		document.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);
		return document;
	}


    rapidjson::Value json::Null() {
        rapidjson::Value value(rapidjson::kNullType);
        return value;
    }
    rapidjson::Value json::NewObject() {
        rapidjson::Value value(rapidjson::kObjectType);
        return value;
    }
    rapidjson::Value json::NewArray() {
        rapidjson::Value value(rapidjson::kArrayType);
        return value;
    }




    rapidjson::Value& json::Get(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) {
			rapidjson::Value null = json::Null();
			return null;
		}
        return node.GetObject()[label];
    }
    std::string json::GetString(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return "";
        return node.GetObject()[label].GetString();
    }
    bool json::GetBool(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return false;
        return node.GetObject()[label].GetBool();
    }
    double json::GetDouble(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetDouble();
    }
    uint8_t json::GetUint8(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint();
    }
    uint16_t json::GetUint16(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint();
    }
    uint32_t json::GetUint(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint();
    }
    uint64_t json::GetUint64(rapidjson::Document& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint64();
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
    void json::Set(rapidjson::Document& node, const std::string& label, uint8_t value) {
		json::Set(node, label, rapidjson::Value{}.SetUint(value));
	}
    void json::Set(rapidjson::Document& node, const std::string& label, uint16_t value) {
		json::Set(node, label, rapidjson::Value{}.SetUint(value));
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


	
    
    rapidjson::Value& json::Get(rapidjson::Value& node, const char* label) {
		if (!node.GetObject().HasMember(label)) {
			rapidjson::Value null = json::Null();
			return null;
		}
        return node.GetObject()[label];
    }
    std::string json::GetString(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return "";
        return node.GetObject()[label].GetString();
    }
    bool json::GetBool(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return false;
        return node.GetObject()[label].GetBool();
    }
    double json::GetDouble(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetDouble();
    }
    uint8_t json::GetUint8(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint();
    }
    uint16_t json::GetUint16(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint();
    }
    uint32_t json::GetUint(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint();
    }
    uint64_t json::GetUint64(rapidjson::Value& node, const char* label) {
        if (!node.GetObject().HasMember(label)) return 0;
        return node.GetObject()[label].GetUint64();
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
    void json::Set(rapidjson::Value& node, const std::string& label, uint8_t value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetUint(value), allocator);
	}
    void json::Set(rapidjson::Value& node, const std::string& label, uint16_t value, rapidjson::Document::AllocatorType& allocator) {
		json::Set(node, label, rapidjson::Value{}.SetUint(value), allocator);
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
