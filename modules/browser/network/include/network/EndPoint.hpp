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

		EndPoint() = default;
		EndPoint(Family family, std::string ip, uint16_t port) : m_family(family), m_ip(std::move(ip)), m_port(port) {}

		Family GetFamily() const noexcept {
			return m_family;
		}
		const std::string& GetIp() const noexcept {
			return m_ip;
		}
		uint16_t GetPort() const noexcept {
			return m_port;
		}

	private:
		Family m_family = Family::IPv4;
		std::string m_ip;
		uint16_t m_port = 0;
	};
}