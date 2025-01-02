
#ifndef _HTTP_URI_HEADER
#define _HTTP_URI_HEADER

// Include
#include "utils/functions.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <array>
#include <map>

// HTTP
namespace HTTP {
	// URI
	class URI {
		public:
			static std::string encode(std::string_view str);
			static std::string decode(std::string_view str);

			void parse(std::string_view path);
			
			decltype(auto) begin() { return mQuery.begin(); }
			decltype(auto) begin() const { return mQuery.begin(); }
			decltype(auto) end() { return mQuery.end(); }
			decltype(auto) end() const { return mQuery.end(); }

			decltype(auto) find(const std::string& name) { return mQuery.find(name); }
			decltype(auto) find(const std::string& name) const { return mQuery.find(name); }

			bool empty() const { return mQuery.empty(); }

			const std::string& protocol() const;
			const std::string& domain() const;
			const std::string& resource() const;
			uint16_t port() const;

			std::string parameter(const std::string& name) const;

			template<typename T>
			std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_enum_v<T>, T> parameter(const std::string& name) const {
				return utils::to_number<T>(parameter(name));
			}

			void set_parameter(const std::string& name, const std::string& value);

		private:
			size_t parse_scheme(std::string_view path, size_t offset = 0);
			size_t parse_authority(std::string_view path, size_t offset = 0);

			void parse_path(std::string_view path, size_t offset = 0);
			void parse_query(std::string_view query);

		private:
			std::map<std::string, std::string> mQuery;

			std::string mProtocol;
			std::string mDomain;
			std::string mResource;
			std::string mFragment;

			uint16_t mPort = 0;
	};
}

#endif
