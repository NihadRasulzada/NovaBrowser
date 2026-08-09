#pragma once

#include <string>
#include <cstdint>

namespace Browser::Network
{
	class EndPoint
	{
	public:
		enum class Family
		{
			IPv4,
			IPv6
		};

		EndPoint();
		EndPoint(Family family, std::string ip, uint16_t port);

		Family GetFamily() const;
		const std::string& GetIp() const;
		uint16_t GetPort() const;

	private:
		Family m_family;
		std::string m_ip;
		uint16_t m_port;
	};
}