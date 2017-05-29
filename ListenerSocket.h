#ifndef _LISTENERSOCKET_H_
#define _LISTENERSOCKET_H_

#include "BaseSocket.h"

class ListenerSocket : public BaseSocket
{
public:
	ListenerSocket();
	virtual ~ListenerSocket();

	bool listen(uint16_t port);
	//bool listen(const char *addr, uint16_t port);

	bool accept();
};

#endif // _LISTENERSOCKET_H_
