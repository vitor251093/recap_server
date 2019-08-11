
// Include
#include "json.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

// utils
namespace utils {

    jsonObject jsonDocumentObject::GetObject(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return jsonObject(rapidAllocator, rapidDocument.GetObject()[rapidLabel]);
    }
    jsonArray jsonDocumentObject::GetArray(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return jsonArray(rapidAllocator, rapidDocument.GetObject()[rapidLabel]);
    }
    bool jsonDocumentObject::GetBool(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidDocument.GetObject()[rapidLabel].GetBool();
    }
    double jsonDocumentObject::GetDouble(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidDocument.GetObject()[rapidLabel].GetDouble();
    }
    uint32_t jsonDocumentObject::GetUint(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidDocument.GetObject()[rapidLabel].GetUint();
    }
    uint64_t jsonDocumentObject::GetUint64(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidDocument.GetObject()[rapidLabel].GetUint64();
    }
    std::string jsonDocumentObject::GetString(const std::string& label) {
        if (!rapidDocument.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidDocument.GetObject()[rapidLabel].GetString();
    }
    jsonObject jsonDocumentObject::NewObject(const std::string& label) {
        rapidjson::Value object(rapidjson::kObjectType);
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        rapidDocument.AddMember(rapidLabel, object, allocator);
        return jsonObject(rapidAllocator, object);
    }
    jsonArray jsonDocumentObject::NewArray(const std::string& label) {
        rapidjson::Value value(rapidjson::kArrayType);
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        rapidDocument.AddMember(rapidLabel, object, allocator);
        return jsonArray(rapidAllocator, object);
    }
    void jsonDocumentObject::Set(const std::string& label, bool value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetBool(value);
        rapidDocument.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
	}
    void jsonDocumentObject::Set(const std::string& label, double value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetDouble(value);
        rapidDocument.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
	}
    void jsonDocumentObject::Set(const std::string& label, uint32_t value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetUint(value);
        rapidDocument.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
    }
    void jsonDocumentObject::Set(const std::string& label, uint64_t value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetUint64(value);
        rapidDocument.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
    }
    void jsonDocumentObject::Set(const std::string& label, const std::string& value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetString(value.c_str(), value.length(), rapidAllocator);
        rapidDocument.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
	}
    std::string jsonDocumentObject::ToString() {
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		rapidDocument.Accept(writer);

		return buffer.GetString();
	}





    jsonObject jsonDocumentArray::GetObject(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return jsonObject(rapidAllocator, rapidDocument.GetArray()[index]);
    }
    jsonArray jsonDocumentArray::GetArray(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return jsonArray(rapidAllocator, rapidDocument.GetArray()[index]);
    }
    bool jsonDocumentArray::GetBool(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return rapidDocument.GetArray()[index].GetBool();
    }
    double jsonDocumentArray::GetDouble(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return rapidDocument.GetArray()[index].GetDouble();
    }
    uint32_t jsonDocumentArray::GetUint(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return rapidDocument.GetArray()[index].GetUint();
    }
    uint64_t jsonDocumentArray::GetUint64(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return rapidDocument.GetArray()[index].GetUint64();
    }
    std::string jsonDocumentArray::GetString(rapidjson::SizeType index) {
        if (index >= rapidDocument.Size()) return NULL;
        return rapidDocument.GetArray()[index].GetString();
    }
    jsonObject jsonDocumentArray::NewObject() {
        rapidjson::Value object(rapidjson::kObjectType);
        rapidDocument.PushBack(object, rapidAllocator);
        return jsonObject(rapidAllocator, object);
    }
    jsonArray jsonDocumentArray::NewArray() {
        rapidjson::Value object(rapidjson::kArrayType);
        rapidDocument.PushBack(object, rapidAllocator);
        return jsonArray(rapidAllocator, object);
    }
    void jsonDocumentArray::Add(bool value) {
        auto rapidObjValue = rapidjson::Value{}.SetBool(value);
        rapidDocument.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonDocumentArray::Add(double value) {
        auto rapidObjValue = rapidjson::Value{}.SetDouble(value);
        rapidDocument.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonDocumentArray::Add(uint32_t value) {
        auto rapidObjValue = rapidjson::Value{}.SetUint(value);
        rapidDocument.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonDocumentArray::Add(uint64_t value) {
        auto rapidObjValue = rapidjson::Value{}.SetUint64(value);
        rapidDocument.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonDocumentArray::Add(const std::string& value) {
        auto rapidObjValue = rapidjson::Value{}.SetString(value.c_str(), value.length(), rapidAllocator);
        rapidDocument.PushBack(rapidObjValue, rapidAllocator);
    }
    std::string jsonDocumentArray::ToString() {
		rapidjson::StringBuffer buffer;
		buffer.Clear();

		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		rapidDocument.Accept(writer);

		return buffer.GetString();
	}





    
    jsonObject jsonObject::GetObject(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return jsonObject(rapidAllocator, rapidValue.GetObject()[rapidLabel]);
    }
    jsonArray jsonObject::GetArray(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return jsonArray(rapidAllocator, rapidValue.GetObject()[rapidLabel]);
    }
    bool jsonObject::GetBool(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidValue.GetObject()[rapidLabel].GetBool();
    }
    double jsonObject::GetDouble(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidValue.GetObject()[rapidLabel].GetDouble();
    }
    uint32_t jsonObject::GetUint(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidValue.GetObject()[rapidLabel].GetUint();
    }
    uint64_t jsonObject::GetUint64(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidValue.GetObject()[rapidLabel].GetUint64();
    }
    std::string jsonObject::GetString(const std::string& label) {
        if (!rapidValue.HasMember(label)) return NULL;
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        return rapidValue.GetObject()[rapidLabel].GetString();
    }
    jsonObject jsonObject::NewObject(const std::string& label) {
        rapidjson::Value object(rapidjson::kObjectType);
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        rapidValue.AddMember(rapidLabel, object, allocator);
        return jsonObject(rapidAllocator, object);
    }
    jsonArray jsonObject::NewArray(const std::string& label) {
        rapidjson::Value value(rapidjson::kArrayType);
        auto rapidLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        rapidValue.AddMember(rapidLabel, object, allocator);
        return jsonArray(rapidAllocator, object);
    }
    void jsonObject::Set(const std::string& label, bool value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetBool(value);
        rapidValue.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
	}
    void jsonObject::Set(const std::string& label, double value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetDouble(value);
        rapidValue.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
	}
    void jsonObject::Set(const std::string& label, uint32_t value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetUint(value);
        rapidValue.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
    }
    void jsonObject::Set(const std::string& label, uint64_t value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetUint64(value);
        rapidValue.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
    }
    void jsonObject::Set(const std::string& label, const std::string& value) {
        auto rapidObjLabel = rapidjson::Value{}.SetString(label.c_str(), label.length(), rapidAllocator);
        auto rapidObjValue = rapidjson::Value{}.SetString(value.c_str(), value.length(), rapidAllocator);
        rapidValue.AddMember(rapidObjLabel, rapidObjValue, rapidAllocator);
	}





    jsonObject jsonArray::GetObject(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return jsonObject(rapidAllocator, rapidValue.GetArray()[index]);
    }
    jsonArray jsonArray::GetArray(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return jsonArray(rapidAllocator, rapidValue.GetArray()[index]);
    }
    bool jsonArray::GetBool(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return rapidValue.GetArray()[index].GetBool();
    }
    double jsonArray::GetDouble(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return rapidValue.GetArray()[index].GetDouble();
    }
    uint32_t jsonArray::GetUint(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return rapidValue.GetArray()[index].GetUint();
    }
    uint64_t jsonArray::GetUint64(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return rapidValue.GetArray()[index].GetUint64();
    }
    std::string jsonArray::GetString(rapidjson::SizeType index) {
        if (index >= rapidValue.Size()) return NULL;
        return rapidValue.GetArray()[index].GetString();
    }
    jsonObject jsonArray::NewObject() {
        rapidjson::Value object(rapidjson::kObjectType);
        rapidValue.PushBack(value, rapidAllocator);
        return jsonObject(rapidAllocator, value);
    }
    jsonArray jsonArray::NewArray() {
        rapidjson::Value object(rapidjson::kArrayType);
        rapidValue.PushBack(value, rapidAllocator);
        return jsonArray(rapidAllocator, value);
    }
    void jsonArray::Add(bool value) {
        auto rapidObjValue = rapidjson::Value{}.SetBool(value);
        rapidValue.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonArray::Add(double value) {
        auto rapidObjValue = rapidjson::Value{}.SetDouble(value);
        rapidValue.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonArray::Add(uint32_t value) {
        auto rapidObjValue = rapidjson::Value{}.SetUint(value);
        rapidValue.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonArray::Add(uint64_t value) {
        auto rapidObjValue = rapidjson::Value{}.SetUint64(value);
        rapidValue.PushBack(rapidObjValue, rapidAllocator);
    }
    void jsonArray::Add(const std::string& value) {
        auto rapidObjValue = rapidjson::Value{}.SetString(value.c_str(), value.length(), rapidAllocator);
        rapidValue.PushBack(rapidObjValue, rapidAllocator);
    }
}