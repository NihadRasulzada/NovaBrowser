#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "EndPoint.hpp"

namespace Browser::Network
{
	class DnsResolver
	{
	public:
		std::vector<EndPoint> Resolve(const std::string& host, uint16_t port) const;
	};
}