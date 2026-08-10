#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>

#include "DnsResolver.hpp"
#include "TcpSocket.hpp"

namespace Browser::Network
{
	class Connection
	{
	public:
		void Connect(const std::string& host, uint16_t port);
		void Disconnect();

		std::size_t Send(std::span<const std::byte> data);
		std::size_t Receive(std::span<std::byte> buffer);

		bool IsOpen() const noexcept;

	private:
		TcpSocket m_socket;
		DnsResolver m_dns;
	};
}