
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
#include <iterator>

#ifdef _MSC_VER
#undef GetObject
#endif

// utils
namespace utils {

    class jsonDocumentArrayIterator
    {
        private:
            jsonDocumentArray rapidDoc;
            rapidjson::SizeType index;
            class jsonDocumentArrayIteratorHolder
            {
                jsonDocumentArray rapidDoc;
                rapidjson::SizeType index;
                public:
                    jsonDocumentArrayIteratorHolder(jsonDocumentArray& doc, rapidjson::SizeType index): rapidDoc(doc), index(index) {}
                    auto GetAsObject()  {return rapidDoc.GetObject(index);};
                    auto GetAsArray()   {return rapidDoc.GetArray(index);};
                    auto GetAsBool()    {return rapidDoc.GetBool(index);};
                    auto GetAsDouble()  {return rapidDoc.GetDouble(index);};
                    auto GetAsUint()    {return rapidDoc.GetUint(index);};
                    auto GetAsUint64()  {return rapidDoc.GetUint64(index);};
                    auto GetAsString()  {return rapidDoc.GetString(index);};
            };
        public:
            jsonDocumentArrayIterator(jsonDocumentArray& doc, rapidjson::SizeType index) : rapidDoc(doc), index(index) {}

            int operator*() const { return jsonDocumentArrayIteratorHolder(rapidDoc, index); }
            bool operator==(const jsonDocumentArrayIterator& other) const { return index == other.index; }
            bool operator!=(const jsonDocumentArrayIterator& other) const { return !(*this == other); }
            jsonDocumentArrayIterator& operator++() {++index;return *this;}
            jsonDocumentArrayIterator operator++(int) {jsonDocumentArrayIterator tmp(*this); operator++(); return tmp;}
    };

    class jsonArrayIterator
    {
        private:
            jsonArray rapidDoc;
            rapidjson::SizeType index;
            class jsonArrayIteratorHolder
            {
                jsonArray rapidDoc;
                rapidjson::SizeType index;
                public:
                    jsonArrayIteratorHolder(jsonArray& doc, rapidjson::SizeType index): rapidDoc(doc), index(index) {}
                    auto GetAsObject()  {return rapidDoc.GetObject(index);};
                    auto GetAsArray()   {return rapidDoc.GetArray(index);};
                    auto GetAsBool()    {return rapidDoc.GetBool(index);};
                    auto GetAsDouble()  {return rapidDoc.GetDouble(index);};
                    auto GetAsUint()    {return rapidDoc.GetUint(index);};
                    auto GetAsUint64()  {return rapidDoc.GetUint64(index);};
                    auto GetAsString()  {return rapidDoc.GetString(index);};
            };
        public:
            jsonArrayIterator(jsonArray& doc, rapidjson::SizeType index) : rapidDoc(doc), index(index) {}

            int operator*() const { return jsonArrayIteratorHolder(rapidDoc, index); }
            bool operator==(const jsonArrayIterator& other) const { return index == other.index; }
            bool operator!=(const jsonArrayIterator& other) const { return !(*this == other); }
            jsonArrayIterator& operator++() {++index;return *this;}
            jsonArrayIterator operator++(int) {jsonArrayIterator tmp(*this); operator++(); return tmp;}
    };




    class jsonDocumentObject {
        public:
            jsonDocumentObject(const std::string& postBody) {
                rapidDocument = rapidjson::Document();
                rapidDocument.Parse(postBody);
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetObject();
            };
            jsonDocumentObject(rapidjson::Document& newDoc) : rapidDocument(newDoc) {
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetObject();
            }
            jsonDocumentObject() : jsonDocumentObject(rapidjson::Document()) {}

             jsonObject GetObject(const std::string& label);
              jsonArray GetArray( const std::string& label);
                   bool GetBool(  const std::string& label);
                 double GetDouble(const std::string& label);
               uint32_t GetUint(  const std::string& label);
               uint64_t GetUint64(const std::string& label);
            std::string GetString(const std::string& label);
            
            jsonObject NewObject(const std::string& label);
             jsonArray NewArray( const std::string& label);
            void Set(const std::string& label, bool value);
            void Set(const std::string& label, double value);
            void Set(const std::string& label, uint32_t value);
            void Set(const std::string& label, uint64_t value);
            void Set(const std::string& label, const std::string& value);
            
            std::string ToString();
        private:
            rapidjson::Document::AllocatorType rapidAllocator;
            rapidjson::Document rapidDocument;
    }

    class jsonDocumentArray {
        public:
            jsonDocumentArray(const std::string& postBody) {
                rapidDocument = rapidjson::Document();
                rapidDocument.Parse(postBody);
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetArray();
            }
            jsonDocumentArray(rapidjson::Document& newDoc) : rapidDocument(newDoc) {
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetArray();
            }
            jsonDocumentArray() : jsonDocumentArray(rapidjson::Document()) {}

            auto Size() {return rapidDocument.GetArray().Size();}
            
             jsonObject GetObject(rapidjson::SizeType index);
              jsonArray GetArray( rapidjson::SizeType index);
                   bool GetBool(  rapidjson::SizeType index);
                 double GetDouble(rapidjson::SizeType index);
               uint32_t GetUint(  rapidjson::SizeType index);
               uint64_t GetUint64(rapidjson::SizeType index);
            std::string GetString(rapidjson::SizeType index);

            jsonObject NewObject();
             jsonArray NewArray();
            void Add(bool value);
            void Add(double value);
            void Add(uint32_t value);
            void Add(uint64_t value);
            void Add(const std::string& value);

            std::string ToString();

            decltype(auto) begin() { return jsonDocumentArrayIterator(this, 0); }
            decltype(auto) end()   { return jsonDocumentArrayIterator(this, Size() - 1); }
        private:
            rapidjson::Document::AllocatorType rapidAllocator;
            rapidjson::Document rapidDocument;
    }

    class jsonObject {
        public:
            jsonObject(rapidjson::Document::AllocatorType& allocator, rapidjson::Value& newVal) : rapidAllocator(allocator), rapidValue(newVal) {
                rapidValue.SetObject();
            }
            
             jsonObject GetObject(const std::string& label);
              jsonArray GetArray( const std::string& label);
                   bool GetBool(  const std::string& label);
                 double GetDouble(const std::string& label);
               uint32_t GetUint(  const std::string& label);
               uint64_t GetUint64(const std::string& label);
            std::string GetString(const std::string& label);
            
            jsonObject NewObject(const std::string& label);
             jsonArray NewArray( const std::string& label);
            void Set(const std::string& label, bool value);
            void Set(const std::string& label, double value);
            void Set(const std::string& label, uint32_t value);
            void Set(const std::string& label, uint64_t value);
            void Set(const std::string& label, const std::string& value);
        private:
            rapidjson::Document::AllocatorType rapidAllocator;
            rapidjson::Value rapidValue;
    }
    
    class jsonArray {
        public:
            jsonArray(rapidjson::Document::AllocatorType& allocator, rapidjson::Value& newVal) : rapidAllocator(allocator), rapidValue(newVal) {
                rapidValue.SetArray();
            }

            rapidjson::SizeType Size() {return rapidValue.GetArray().Size();}
            
             jsonObject GetObject(rapidjson::SizeType index);
              jsonArray GetArray( rapidjson::SizeType index);
                   bool GetBool(  rapidjson::SizeType index);
                 double GetDouble(rapidjson::SizeType index);
               uint32_t GetUint(  rapidjson::SizeType index);
               uint64_t GetUint64(rapidjson::SizeType index);
            std::string GetString(rapidjson::SizeType index);

            jsonObject NewObject();
             jsonArray NewArray();
            void Add(bool value);
            void Add(double value);
            void Add(uint32_t value);
            void Add(uint64_t value);
            void Add(const std::string& value);

            decltype(auto) begin() { return jsonArrayIterator(this, 0); }
            decltype(auto) end()   { return jsonArrayIterator(this, Size() - 1); }
        private:
            rapidjson::Document::AllocatorType rapidAllocator;
            rapidjson::Value rapidValue;
    }
}

#endif
