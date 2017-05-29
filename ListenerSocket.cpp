#include "ListenerSocket.h"


ListenerSocket::ListenerSocket()
	: BaseSocket()
{
}

ListenerSocket::~ListenerSocket()
{
}

bool ListenerSocket::listen(uint16_t port)
{
	if (createSocket() == false)
	{
		return false;
	}

	// TODO: set
	struct sockaddr addr;

	if (::bind(m_s, &addr, 0) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

/*
bool ListenerSocket::listen(const char *addr, uint16_t port)
{
	if (createSocket() == false)
	{
		return false;
	}
}
*/

bool ListenerSocket::accept()
{
	int res = listen(m_s);
	if (res == SOCKET_ERROR)
	{
		return false;
	}

	struct sockaddr addr;
	int len = sizeof(sockaddr);

	SOCKET s = ::accept(m_s, &addr, &len);
	if (s == INVALID_SOCKET)
	{
		return false;
	}

	// TODO: check incoming address (if necessary)
	//isValidPeer(addr)

	// do something with this
	BaseSocket client(s);

	return true;
}
