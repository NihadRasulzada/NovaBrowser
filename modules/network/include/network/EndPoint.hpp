#pragma once

#include <string>
#include <cstdint>

namespace Browser::Network
{
	class EndPoint
	{
	public:
		EndPoint() = default;

		EndPoint(std::string host, uint16_t port);

		const std::string& Host() const noexcept;

		uint16_t Port() const noexcept;

	private:
		std::string m_host;
		uint16_t m_port = 0;
	};
}