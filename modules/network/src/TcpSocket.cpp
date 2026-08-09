#include "TcpSocket.hpp"

namespace Browser::Network {
	TcpSocket::TcpSocket()
	{
		CreateSocket();
	}

	void TcpSocket::CreateSocket() {
#ifdef BROWSER_WINDOWS
		m_handle = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
		m_handle = ::socket(AF_INET, SOCK_STREAM, 0);
#endif
		if (!IsOpen()) {
			throw NetworkException("Failed to create TCP socket");
		}
	}

	bool TcpSocket::IsOpen() const
	{
#ifdef BROWSER_WINDOWS
		return m_handle != INVALID_SOCKET;
#else
		return m_handle != -1;
#endif
	}

	void TcpSocket::Close()
	{
#ifdef BROWSER_WINDOWS
		closesocket(m_handle);
		m_handle = INVALID_SOCKET;
#else
		close(m_handle);
		m_handle = -1;
#endif
	}

	void TcpSocket::Connect(const EndPoint& endpoint)
	{
		sockaddr_in address{};

		address.sin_family = AF_INET;

		address.sin_port = htons(endpoint.GetPort());

		inet_pton(AF_INET, endpoint.GetIp().c_str(), &address.sin_addr);

		auto result = connect(m_handle, reinterpret_cast<sockaddr*>(&address), sizeof(address));

		if (result != 0)
		{
			throw NetworkException(
				"Connect failed");
		}
	}
}