#include "network/DnsResolver.hpp"
#include "network/NetworkException.hpp"

#include <cstring>
#include <string>

#if BROWSER_PLATFORM_WINDOWS

#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

#endif

namespace Browser::Network
{
    std::vector<EndPoint> DnsResolver::Resolve(
        const std::string& host,
        uint16_t port) const
    {
        addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        addrinfo* result = nullptr;

        const std::string service =
            std::to_string(port);

        const int error = getaddrinfo(
            host.c_str(),
            service.c_str(),
            &hints,
            &result);

        if (error != 0)
        {
#if BROWSER_PLATFORM_WINDOWS

            throw NetworkException(
                "DNS resolution failed: " +
                std::to_string(error));

#else

            throw NetworkException(
                "DNS resolution failed: " +
                std::string(gai_strerror(error)));

#endif
        }

        std::vector<EndPoint> endpoints;

        for (
            addrinfo* current = result;
            current != nullptr;
            current = current->ai_next)
        {
            char buffer[INET6_ADDRSTRLEN]{};

            if (current->ai_family == AF_INET)
            {
                const auto* address =
                    reinterpret_cast<const sockaddr_in*>(
                        current->ai_addr);

                const char* resultAddress =
                    inet_ntop(
                        AF_INET,
                        &address->sin_addr,
                        buffer,
                        sizeof(buffer));

                if (resultAddress == nullptr)
                {
                    continue;
                }

                endpoints.emplace_back(
                    EndPoint::Family::IPv4,
                    buffer,
                    port);
            }
            else if (current->ai_family == AF_INET6)
            {
                const auto* address =
                    reinterpret_cast<const sockaddr_in6*>(
                        current->ai_addr);

                const char* resultAddress =
                    inet_ntop(
                        AF_INET6,
                        &address->sin6_addr,
                        buffer,
                        sizeof(buffer));

                if (resultAddress == nullptr)
                {
                    continue;
                }

                endpoints.emplace_back(
                    EndPoint::Family::IPv6,
                    buffer,
                    port);
            }
        }

        freeaddrinfo(result);

        return endpoints;
    }
}