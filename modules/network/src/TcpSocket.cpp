#include "network/TcpSocket.hpp"
#include "network/NetworkException.hpp"

#include <limits>

#if BROWSER_PLATFORM_WINDOWS

#include <winsock2.h>
#include <ws2tcpip.h>

#else

#include <arpa/inet.h>
#include <cerrno>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#endif

namespace Browser::Network {
	void TcpSocket::CreateSocket(EndPoint::Family family) {
		Close();

		int addressFamily = (family == EndPoint::Family::IPv4) ? AF_INET : AF_INET6;

#if BROWSER_PLATFORM_WINDOWS
		m_handle = ::socket(addressFamily, SOCK_STREAM, IPPROTO_TCP);
#else
		m_handle = ::socket(addressFamily, SOCK_STREAM, 0);
#endif

		if (!IsOpen()) {
			throw NetworkException("Failed to create socket");
		}
	}

	void TcpSocket::Connect(const EndPoint& endpoint) {
		CreateSocket(endpoint.GetFamily());

		if (endpoint.GetFamily() == EndPoint::Family::IPv4)
		{
			ConnectIPv4(endpoint);
		}
		else
		{
			ConnectIPv6(endpoint);
		}
	}

	void TcpSocket::ConnectIPv4(const EndPoint& endpoint) {
		sockaddr_in address{};

		address.sin_family = AF_INET;
		address.sin_port = htons(endpoint.GetPort());

		const int result = inet_pton(AF_INET, endpoint.GetIp().c_str(), &address.sin_addr);

		if (result != 1) {
			throw NetworkException("Invalid IPv4 address");
		}

		const int connectResult = ::connect(m_handle, reinterpret_cast<const sockaddr*>(&address), sizeof(address));

		if (connectResult != 0) {
			Close();

			throw NetworkException("IPv4 connection failed");
		}
	}

	void TcpSocket::ConnectIPv6(const EndPoint& endpoint) {
		sockaddr_in6 address{};

		address.sin6_family = AF_INET6;
		address.sin6_port = htons(endpoint.GetPort());

		const int result = inet_pton(AF_INET6, endpoint.GetIp().c_str(), &address.sin6_addr);

		if (result != 1) {
			throw NetworkException("Invalid IPv6 address");
		}

		const int connectResult = ::connect(m_handle, reinterpret_cast<const sockaddr*>(&address), sizeof(address));

		if (connectResult != 0) {
			Close();

			throw NetworkException("IPv6 connection failed");
		}
	}

	std::size_t TcpSocket::Send(
		std::span<const std::byte> data)
	{
		if (!IsOpen())
		{
			throw NetworkException(
				"Cannot send on a closed socket");
		}

		if (data.empty())
		{
			return 0;
		}

#if BROWSER_PLATFORM_WINDOWS

		const auto length = static_cast<int>(
			std::min(
				data.size(),
				static_cast<std::size_t>(
					std::numeric_limits<int>::max())));

		const int result = ::send(
			m_handle,
			reinterpret_cast<const char*>(data.data()),
			length,
			0);

		if (result == SOCKET_ERROR)
		{
			throw NetworkException(
				"Socket send failed");
		}

		return static_cast<std::size_t>(result);

#else

		const ssize_t result = ::send(
			m_handle,
			data.data(),
			data.size(),
			0);

		if (result < 0)
		{
			throw NetworkException(
				"Socket send failed");
		}

		return static_cast<std::size_t>(result);

#endif
	}

	std::size_t TcpSocket::Receive(
		std::span<std::byte> buffer)
	{
		if (!IsOpen())
		{
			throw NetworkException(
				"Cannot receive from a closed socket");
		}

		if (buffer.empty())
		{
			return 0;
		}

#if BROWSER_PLATFORM_WINDOWS

		const auto length = static_cast<int>(
			std::min(
				buffer.size(),
				static_cast<std::size_t>(
					std::numeric_limits<int>::max())));

		const int result = ::recv(
			m_handle,
			reinterpret_cast<char*>(buffer.data()),
			length,
			0);

		if (result == SOCKET_ERROR)
		{
			throw NetworkException(
				"Socket receive failed");
		}

		return static_cast<std::size_t>(result);

#else

		const ssize_t result = ::recv(
			m_handle,
			buffer.data(),
			buffer.size(),
			0);

		if (result < 0)
		{
			throw NetworkException(
				"Socket receive failed");
		}

		return static_cast<std::size_t>(result);

#endif
	}
}