#pragma once

#include <string>
#include <cstdint>

namespace Browser::Network {
	class Address {
	public:
		virtual ~Address() = default;

		virtual std::string ToString() const = 0;
		virtual uint16_t Port() const = 0;
	};
}