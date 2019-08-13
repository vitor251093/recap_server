
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

    class jsonArrayGeneric;
    class jsonObjectGeneric;
    class jsonArrayIterator;

    class jsonArrayGeneric
    {
        public:
            virtual  jsonObjectGeneric GetObject(rapidjson::SizeType index) = 0;
            virtual   jsonArrayGeneric GetArray( rapidjson::SizeType index) = 0;
            virtual        bool GetBool(  rapidjson::SizeType index) = 0;
            virtual      double GetDouble(rapidjson::SizeType index) = 0;
            virtual    uint32_t GetUint(  rapidjson::SizeType index) = 0;
            virtual    uint64_t GetUint64(rapidjson::SizeType index) = 0;
            virtual std::string GetString(rapidjson::SizeType index) = 0;

            virtual jsonObjectGeneric NewObject() = 0;
            virtual  jsonArrayGeneric NewArray() = 0;
            virtual void Add(bool value) = 0;
            virtual void Add(double value) = 0;
            virtual void Add(uint32_t value) = 0;
            virtual void Add(uint64_t value) = 0;
            virtual void Add(const std::string& value) = 0;

            virtual rapidjson::SizeType Size() = 0;
            jsonArrayIterator begin() { return jsonArrayIterator(this, 0); }
            jsonArrayIterator end()   { return jsonArrayIterator(this, Size() - 1); }

        private:
            rapidjson::Document::AllocatorType rapidAllocator;
    }
    class jsonObjectGeneric
    {
        public:
            virtual  jsonObjectGeneric GetObject(const std::string& label);
            virtual   jsonArrayGeneric GetArray( const std::string& label);
            virtual        bool GetBool(  const std::string& label);
            virtual      double GetDouble(const std::string& label);
            virtual    uint32_t GetUint(  const std::string& label);
            virtual    uint64_t GetUint64(const std::string& label);
            virtual std::string GetString(const std::string& label);
            
            virtual jsonObjectGeneric NewObject(const std::string& label);
            virtual  jsonArrayGeneric NewArray( const std::string& label);
            virtual void Set(const std::string& label, bool value);
            virtual void Set(const std::string& label, double value);
            virtual void Set(const std::string& label, uint32_t value);
            virtual void Set(const std::string& label, uint64_t value);
            virtual void Set(const std::string& label, const std::string& value);

        private:
            rapidjson::Document::AllocatorType rapidAllocator;
    }



    class jsonArrayElement
    {
        jsonArrayGeneric parent;
        rapidjson::SizeType index;
        public:
            jsonArrayElement(jsonArrayGeneric& doc, rapidjson::SizeType index): parent(doc), index(index) {}
            auto GetAsObject()  {return parent.GetObject(index);};
            auto GetAsArray()   {return parent.GetArray(index);};
            auto GetAsBool()    {return parent.GetBool(index);};
            auto GetAsDouble()  {return parent.GetDouble(index);};
            auto GetAsUint()    {return parent.GetUint(index);};
            auto GetAsUint64()  {return parent.GetUint64(index);};
            auto GetAsString()  {return parent.GetString(index);};
    };
    class jsonArrayIterator
    {
        private:
            jsonArrayGeneric rapidDoc;
            rapidjson::SizeType index;
        public:
            jsonArrayIterator(jsonArrayGeneric& doc, rapidjson::SizeType index) : rapidDoc(doc), index(index) {}

            int operator*() const { return jsonArrayElement(rapidDoc, index); }
            bool operator==(const jsonArrayIterator& other) const { return index == other.index; }
            bool operator!=(const jsonArrayIterator& other) const { return !(*this == other); }
            jsonArrayIterator& operator++() {++index;return *this;}
            jsonArrayIterator operator++(int) {jsonArrayIterator tmp(*this); operator++(); return tmp;}
    };




    class jsonDocumentObject : public jsonObjectGeneric {
        public:
            jsonDocumentObject(const std::string& postBody) {
                rapidDocument = rapidjson::Document();
                rapidDocument.Parse(postBody);
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetObject();
            }
            jsonDocumentObject(rapidjson::Document& newDoc) : rapidDocument(newDoc) {
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetObject();
            }
            jsonDocumentObject() {
                rapidDocument = rapidjson::Document();
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetObject();
            }

            std::string ToString();
        private:
            rapidjson::Document rapidDocument;
    }

    class jsonDocumentArray : public jsonArrayGeneric {
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
            jsonDocumentArray() {
                rapidDocument = rapidjson::Document();
                rapidAllocator = rapidDocument.GetAllocator();
                rapidDocument.SetArray();
            }

            rapidjson::SizeType Size() {return rapidDocument.GetArray().Size();}
            
            std::string ToString();
        private:
            rapidjson::Document rapidDocument;
    }

    class jsonObject : public jsonObjectGeneric {
        public:
            jsonObject(rapidjson::Document::AllocatorType& allocator, rapidjson::Value& newVal) : rapidAllocator(allocator), rapidValue(newVal) {
                rapidValue.SetObject();
            }
        private:
            rapidjson::Value rapidValue;
    }
    
    class jsonArray : public jsonArrayGeneric {
        public:
            jsonArray(rapidjson::Document::AllocatorType& allocator, rapidjson::Value& newVal) : rapidAllocator(allocator), rapidValue(newVal) {
                rapidValue.SetArray();
            }

            rapidjson::SizeType Size() {return rapidValue.GetArray().Size();}
        private:
            rapidjson::Value rapidValue;
    }
}

#endif
