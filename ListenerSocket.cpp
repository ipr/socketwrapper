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

	struct sockaddr addr;

	int res = 0;

	res = bind(m_s, );

	res = listen(m_s);

	res = accept(m_s, &addr, );


	if (res < 0)
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
