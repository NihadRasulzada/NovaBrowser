#pragma once

#include "Address.hpp"

namespace Browser::Network {
	class IPv4Address : public Address {
	public:
		IPv4Address();

		IPv4Address(const std::string address, uint16_t port);

		std::string ToString() const override;
		uint16_t Port() const override;

	private:
		std::string m_address;
		uint16_t m_port = 0;
	};
}