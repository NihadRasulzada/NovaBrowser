#pragma once

#include <stdexcept>

namespace Browser::Network {
	class NetworkException : public std::runtime_error {
	public:
		using std::runtime_error::runtime_error;
	};
}