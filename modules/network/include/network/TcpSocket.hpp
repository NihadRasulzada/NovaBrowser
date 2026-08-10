#pragma once

#include "SocketBase.hpp"

namespace Browser::Network {
	class TcpSocket final : public SocketBase {
	public:
		TcpSocket() = default;
		~TcpSocket() override = default;

		void Connect(const EndPoint& endpoint) override;

		std::size_t Send(std::span<const std::byte> data) override;
		std::size_t Receive(std::span<std::byte> buffer) override;

	private:
		void CreateSocket(EndPoint::Family family);
		void ConnectIPv4(const EndPoint& endpoint);
		void ConnectIPv6(const EndPoint& endpoint);
	};
}