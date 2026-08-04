#include "network/SocketBase.hpp"

namespace Browser::Network
{
    SocketBase::~SocketBase()
    {
        if (IsOpen())
        {
            Close();
        }
    }
}