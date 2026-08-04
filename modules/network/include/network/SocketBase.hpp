#pragma once

#include "ISocket.hpp"

#ifdef BROWSER_WINDOWS
#include <winsock2.h>
#else
#include <unistd.h>
#endif

namespace Browser::Network {
	class SocketBase : public ISocket {
	public:
		virtual ~SocketBase();

	protected:
#ifdef BROWSER_WINDOWS
		SOCKET m_handle = INVALID_SOCKET;
#else
		int m_handle = -1;
#endif

	};
}