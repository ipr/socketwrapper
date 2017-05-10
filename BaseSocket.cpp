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
#ifdef _WIN32
	// TODO: make static or something..
	// call once globally in application
	WSADATA wsadata;
	WORD vers = MAKEWORD(2, 2); // no reason to try anything older
	if (WSAStartup(vers, &wsadata) != 0)
	{
		return false;
	}
#endif
	return true;
}

// also, you need to cleanup wsa sockets once per app..
bool cleanupSocket()
{
#ifdef _WIN32
	// TODO: make static or something,
	// call once globally in application
	WSACleanup();
#endif
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
bool BaseSocket::sendData(const size_t length, const char *data)
{
	const int retrylimit = 10; // TODO: make configurable
	int retrycount = 0;
	size_t sent = 0, to_send = length;
	char *pos = (char*)data;
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

// receive data to buffer
bool BaseSocket::recvData(const size_t bufSpace, char *buf, size_t &received)
{
	size_t spaceavailable = bufSpace;
	char *pos = buf;
	int res = 0;
	bool repeatRead = false;

	received = 0; // init

	// TODO: add MSG_PEEK so we don't block when no need
	//
	// note that more data might be waiting after each call, catch what we can:
	// try read at least once
	do
	{
		// note that we might be blocking here if there is no data waiting:
		// add MSG_PEEK to check so we don't block without need
		res = recv(m_s, pos, spaceavailable, 0);
		if (res > 0)
		{
			received += res;
			spaceavailable -= res;
			pos += res;
		}

		/*
		// TODO: test peek-handling
		// more data waiting -> repeat read
		if (recv(m_s, pos, spaceavailable, MSG_PEEK) > 0)
		{
			repeatRead = true;
		}
		*/
	} while (res != SOCKET_ERROR && received < bufSpace && repeatRead == true);
	if (res < 0)
	{
		return false;
	}
	return true;
}

///////////////// ClientSocket

ClientSocket::ClientSocket()
	: BaseSocket()
{
}

ClientSocket::~ClientSocket()
{
	closeSocket();
}

bool ClientSocket::connect(const char *peer, uint16_t port)
{
	if (createSocket() == false)
	{
		return false;
	}

	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(peer);

	int res = ::connect(m_s, (sockaddr*)&saddr, sizeof(sockaddr));
	if (res != 0)
	{
		return false;
	}
	return true;
}

bool ClientSocket::close()
{
	return closeSocket();
}
