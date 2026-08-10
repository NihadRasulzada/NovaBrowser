#include "network/Connection.hpp"
#include "network/NetworkException.hpp"

namespace Browser::Network
{
	void Connection::Connect(const std::string& host, uint16_t port) {
		const auto endpoints = m_dns.Resolve(host, port);

		if (endpoints.empty()) {
			throw NetworkException("DNS returned no addresses for host: " + host);
		}

		NetworkException lastError("Unable to connect");

		for (const auto& endpoint : endpoints) {
			try {
				m_socket.Connect(endpoint);
				return;
			}
			catch (const NetworkException& error) {
				lastError = error;
			}
		}

		throw NetworkException("Unable to connect to host: " + host + ". Last error: " + std::string(lastError.what()));
	}

	void Connection::Disconnect() {
		m_socket.Close();
	}

	std::size_t Connection::Send(std::span<const std::byte> data) {
		return m_socket.Send(data);
	}

	std::size_t Connection::Receive(std::span<std::byte> buffer) {
		return m_socket.Receive(buffer);
	}

	bool Connection::IsOpen() const noexcept {
		return m_socket.IsOpen();
	}
}