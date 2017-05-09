/////////////////////////////
// BaseSocket : wrap socket functionality
//
// Ilkka Prusi 2017
// ilkka.prusi@gmail.com
//
#ifndef _BASESOCKET_H_
#define _BASESOCKET_H_

#include <stdint.h> // ISO-standard types wherever available

#ifdef _WIN32
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

bool startSocket();
bool cleanupSocket();

class BaseSocket
{
protected:
	SOCKET m_s;

	bool createSocket(int proto = IPPROTO_TCP, int type = SOCK_STREAM, int af = AF_INET)
	{
		m_s = socket(af, type, proto);
		if (m_s == INVALID_SOCKET)
		{
			return false;
		}
		return true;
	}

	bool closeSocket()
	{
		if (m_s != INVALID_SOCKET)
		{
			if (closesocket(m_s) == SOCKET_ERROR)
			{
				return false;
			}
			m_s = INVALID_SOCKET;
		}
		return true;
	}
public:
	BaseSocket();
	virtual ~BaseSocket();

	bool sendData(const size_t length, char *data);
	bool recvData(const size_t bufSpace, char *buf, size_t &received);
};

///////////// ClientSocket

class ClientSocket : protected BaseSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();

	bool connect(const char *peer, uint16_t port);
	bool close();
};

#endif //_BASESOCKET_H_
