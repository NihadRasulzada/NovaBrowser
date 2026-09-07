#include "network/SocketBase.hpp"

#if BROWSER_PLATFORM_WINDOWS
#include <winsock2.h>
#else
#include <unistd.h>
#endif

namespace Browser::Network {
	SocketBase::~SocketBase() {
		Close();
	}

	void SocketBase::Close() {
		if (!IsOpen()) {
			return;
		}
#if BROWSER_PLATFORM_WINDOWS
		::closesocket(m_handle);
		m_handle = INVALID_SOCKET;
#else
		::close(m_handle);
		m_handle = -1;
#endif
	}

	bool SocketBase::IsOpen() const noexcept {
#if BROWSER_PLATFORM_WINDOWS
		return m_handle != INVALID_SOCKET;
#else
		return m_handle >= 0;
#endif
	}
}