#include "network/DnsResolver.hpp"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif
#include <network/NetworkException.hpp>

namespace Browser::Network {
	std::vector<EndPoint> DnsResolver::Resolve(const std::string& host, uint16_t port) const
	{
		addrinfo hints = {};

		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		addrinfo* result = nullptr;

		auto error = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result);

		if (error != 0) {
			throw NetworkException(gai_strerror(error));
		}

		std::vector<EndPoint> endpoints;

		for (auto* current = result; current; current = current->ai_next)
		{
			sockaddr_in* address = reinterpret_cast<sockaddr_in*>(current->ai_addr);

			char buffer[64];

			inet_ntop(AF_INET, &address->sin_addr, buffer, sizeof(buffer));

			endpoints.emplace_back(EndPoint::Family::IPv4, buffer, port);
		}
		freeaddrinfo(result);

		return endpoints;
	}
}