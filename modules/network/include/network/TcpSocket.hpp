#pragma once

#include "SocketBase.hpp"

namespace Browser::Network {
	class TcpSocket final : public SocketBase {
	public:
		TcpSocket();
		~TcpSocket();

		void Connect(const EndPoint&) override;

		std::size_t Send(std::span<const std::byte>) override;
		std::size_t Receive(std::span<std::byte>) override;
		void Close() override;
		bool IsOpen() const override;

	private:
		void CreateSocket();
	};
}