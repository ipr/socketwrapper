/////////////////////////////
// BaseSocket : wrap socket functionality
//
// Ilkka Prusi 2017
// ilkka.prusi@gmail.com
//
#include "BaseSocket.h"

// you need to initialize wsa sockets once per app..
bool startSocket()
{
	// TODO: make static or something..
	// call once globally in application
	WSADATA wsadata;
	WORD vers = MAKEWORD(2, 2); // no reason to try anything older
	if (WSAStartup(vers, &wsadata) != 0)
	{
		return false;
	}
	return true;
}

// also, you need to cleanup wsa sockets once per app..
bool cleanupSocket()
{
	// TODO: make static or something,
	// call once globally in application
	WSACleanup();
	return true;
}

BaseSocket::BaseSocket()
	: m_s(INVALID_SOCKET)
{
}

BaseSocket::~BaseSocket()
{
	closeSocket();
}

// transmit data from buffer
bool BaseSocket::sendData(const size_t length, char *data)
{
	const int retrylimit = 10; // TODO: make configurable
	int retrycount = 0;
	size_t sent = 0, to_send = length;
	char *pos = data;
	int res = 0;

	// the way sending works, check amount of each chunk sent in case it is not sent all at once
	// (buffer descriptors reserved)
	while (sent < length && res != SOCKET_ERROR && retrycount < retrylimit)
	{
		// try to send as much as possible at once
		res = send(m_s, pos, to_send, 0);
		if (res > 0)
		{
			// something was sent, update remaining
			sent += res;
			to_send -= res;
			pos += res;
		}
		else if (res == 0)
		{
			// note: zero is valid return (nothing sent), just retry
			retrycount++;
		}
	}
	if (res < 0 || retrycount == retrylimit)
	{
		return false;
	}
	return true;
}

