#pragma once 

#include <cstddef>

#include "ISocket.hpp"
#include "Platform.hpp"

#ifdef BROWSER_PLATFORM_WINDOWS
#include <WinSock2.h>
#else
using SocketHandle = int;
#endif

namespace Browser::Network {
	class SocketBase : public ISocket {
	public:
		~SocketBase() override;

		void Close() override;
		bool IsOpen() const noexcept override;

	protected:
#ifdef	BROWSER_PLATFORM_WINDOWS
		SOCKET m_handle = INVALID_SOCKET;
#else
		int m_handle = -1;
#endif
	};
}
