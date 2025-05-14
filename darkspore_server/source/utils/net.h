#ifndef _UTILS_NET_HEADER
#define _UTILS_NET_HEADER

#include <boost/asio.hpp>

#include <cstdint>
#include <string>

namespace utils {

namespace net {

boost::asio::ip::address resolve_ip(const std::string& hostname, std::uint16_t port)
{
    boost::asio::ip::tcp::resolver::query query(hostname, std::to_string(port));
    boost::asio::ip::tcp::resolver resolver(boost::asio::system_executor{});
    const auto matches = resolver.resolve(query);
    for (auto match : matches)
    {
        // Prefer v4 IPs
        const auto addr = match.endpoint().address();
        if (addr.is_v4())
        {
            return addr;
        }
    }

    // No v4 IP found, return any
    for (auto match : matches)
    {
        return match.endpoint().address();
    }

    // No IP resolved
    return {};
}

}  // namespace net

}  // namespace utils


#endif
