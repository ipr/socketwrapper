// socketwrapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseSocket.h"

#include <string>
#include <vector>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		return -1;
	}
	if (startSocket() == false)
	{
		return -1;
	}

	ClientSocket client;
	if (client.connect(argv[1], 22) == false)
	{
		return -2;
	}

	std::string helo("HELO");
	if (client.sendData(helo.size(), helo.c_str()) == false)
	{
		return -3;
	}

	size_t totalreceived = 0;
	size_t received = 0;
	std::vector<char> data;
	data.resize(1234);
	char *pos = data.data();
	size_t space = data.size();
	bool expectmore = true;
	while (expectmore == true)
	{
		if (client.recvData(space, pos, received) == false)
		{
			break;
		}
		pos += received;
		space -= received;
		totalreceived += received;

		// scan for CRLF, this is ugly, don't do this..
		while (received > 0)
		{
			if (*(pos - received) == '\r' && *(pos - (received-1)) == '\n')
			{
				expectmore = false;
				break;
			}
			--received;
		}
	}

	client.close();
	cleanupSocket();
    return 0;
}

