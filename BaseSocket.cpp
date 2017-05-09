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
}

