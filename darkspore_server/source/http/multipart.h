
#ifndef _HTTP_MULTIPART_HEADER
#define _HTTP_MULTIPART_HEADER

// Include
#include <boost/regex.hpp>

#include <string>
#include <string_view>
#include <map>

// HTTP
namespace HTTP {
	struct Request;

	// Multipart
	class Multipart {
		public:
			Multipart();

			decltype(auto) begin() { return mFields.begin(); }
			decltype(auto) begin() const { return mFields.begin(); }
			decltype(auto) end() { return mFields.end(); }
			decltype(auto) end() const { return mFields.end(); }

			std::string field(const std::string& name);

			void parse(const Request& request);

		private:
			void parse(const std::string& body, const std::string& boundary);

		private:
			std::map<std::string, std::string> mFields;
			std::string mBoundary;

			boost::regex mRegex;
			boost::regex mMultipartRegex;
	};
}

#endif
