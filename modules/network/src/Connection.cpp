#include "network/Connection.hpp"
#include <string>

namespace Browser::Network {
	void Connection::Connect(const std::string& host, uint16_t port) {
		auto endpoints = m_dns.Resolve(host, port);

		if (endpoints.empty())
		{
			throw NetworkException("Host not found");
		}

		for (auto& endpoint : endpoints)
		{
			try
			{
				m_socket.Connect(endpoint);
				return;
			}
			catch (...)
			{
			}
		}

		throw NetworkException("Unable to connect");
	}
}