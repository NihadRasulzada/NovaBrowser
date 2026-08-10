#include "network/NetworkRuntime.hpp"
#include "network/NetworkException.hpp"

#ifdef _WIN32
#include <WinSock2.h>
#endif 

namespace Browser::Network {
	NetworkRuntime::NetworkRuntime() {
#ifdef _WIN32
		WSAData data{};

		const int result = WSAStartup(MAKEWORD(2, 2), &data);

		if (result != 0) {
			throw NetworkException("Failed to initialize Winsock");
		}
#endif
	}

	NetworkRuntime::~NetworkRuntime()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}
}