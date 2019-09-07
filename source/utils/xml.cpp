
// Include
#include "xml.h"
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <pugixml.hpp>

// XML Writer
struct xml_string_writer : pugi::xml_writer {
	std::string result;

	void write(const void* data, size_t size) override {
		result.append(static_cast<const char*>(data), size);
	}
};


// utils
namespace utils {

	void xml::Set(pugi::xml_node& node, const std::string& name, const std::string& value) {
		node.append_child(name.c_str()).append_child(pugi::node_pcdata).set_value(value.c_str());
	}

	std::string xml::GetString(const pugi::xml_node& node, const std::string& name) {
		return node.child(name.c_str()).text().get();
	}

    std::string xml::ToString(pugi::xml_document& document)
    {
        xml_string_writer writer;
		document.save(writer, "\t", 1U, pugi::encoding_latin1);
		return std::move(writer.result);
    }
}