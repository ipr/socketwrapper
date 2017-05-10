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

	size_t received = 0;
	std::vector<char> data;
	data.resize(1234);
	if (client.recvData(data.size(), data.data(), received) == false)
	{
		return -4;
	}
	client.close();
	cleanupSocket();
    return 0;
}

