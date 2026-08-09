#pragma once

#include <cstddef>
#include <span>
#include "EndPoint.hpp"

namespace Browser::Network
{
	class ISocket
	{
	public:
		virtual ~ISocket() = default;
		virtual void Connect(const EndPoint& endpoint) = 0;
		virtual std::size_t Send(std::span<const std::byte> data) = 0;
		virtual std::size_t Receive(std::span<std::byte> buffer) = 0;
		virtual void Close() = 0;
		virtual bool IsOpen() const = 0;
	};
}