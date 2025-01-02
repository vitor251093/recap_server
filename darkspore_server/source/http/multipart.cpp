
// Include
#include "multipart.h"
#include "session.h"

#include "utils/functions.h"

// HTTP
namespace HTTP {
	// Multipart
	Multipart::Multipart() {
		mMultipartRegex = boost::regex(R"_(name\s*=\s*"([a-zA-Z0-9_]+)")_");
		mRegex = boost::regex(R"_(([a-zA-Z0-9_]+)\s*=\s*([a-zA-Z0-9_]+))_");
	}

	std::string Multipart::field(const std::string& name) {
		auto it = mFields.find(name);
		return it != mFields.end() ? it->second : std::string();
	}

	void Multipart::parse(const Request& request) {
		auto contentType = request.data[boost::beast::http::field::content_type];
		auto multipartOffset = contentType.find("multipart");
		if (multipartOffset == std::string_view::npos) {
			return;
		}

		std::string boundary;
		boost::cmatch match;
		if (boost::regex_search(contentType.data(), match, mRegex)) {
			if (match[1] == "boundary") {
				boundary = match[2];
			}
		}

		if (boundary.empty()) {
			return;
		}

		parse(request.data.body(), boundary);
	}

	void Multipart::parse(const std::string& body, const std::string& boundary) {
#if 1
		auto boundaryEnd = body.find("--" + boundary + "--");
		if (boundaryEnd == std::string::npos) {
			return;
		}

		std::string_view bodyView = body;
		bodyView.remove_suffix(body.length() - boundaryEnd);

		const auto& formDataList = utils::explode_string(bodyView, "--" + boundary + "\r\n");
		for (const auto& formData : formDataList) {
			if (!formData.starts_with("Content-Disposition")) {
				continue;
			}

			boost::cmatch match;
			if (boost::regex_search(formData.data(), match, mMultipartRegex)) {
				std::string_view value = formData.substr(match.position() + match.length() + 4);
				value.remove_suffix(2);

				mFields.emplace(match[1], value);
			}
		}
		/*
		auto length = body.length();
		auto position = body.find(boundary);
		while (position != std::string::npos) {
			position += boundary.length();

			std::string_view bodyView(&body[position], length - position);
			if (bodyView.starts_with("Content-Disposition")) {
				std::cmatch match;
				if (std::regex_search(bodyView.data(), match, mMultipartRegex)) {
					if (match[1] == "thumb") {
						#ifdef _MSC_VER
						__debugbreak();
						#endif
					}
					mFields.emplace(match[1], match[2]);
				}
			} else if (bodyView.starts_with("Content-Type")) {
				// Don't care atm.
			}

			position = body.find(boundary, position);
		}
		*/
#else
		auto length = body.length();
		auto position = body.find(boundary);
		while (position != std::string::npos) {
			position += boundary.length();

			std::string_view bodyView(&body[position], length - position);
			if (bodyView.starts_with("Content-Disposition")) {
				std::cmatch match;
				if (std::regex_search(bodyView.data(), match, mMultipartRegex)) {
					if (match[1] == "thumb") {
						#ifdef _MSC_VER
						__debugbreak();
						#endif
					}
					mFields.emplace(match[1], match[2]);
				}
			} else if (bodyView.starts_with("Content-Type")) {
				// Don't care atm.
			}

			position = body.find(boundary, position);
		}
#endif
	}
}
