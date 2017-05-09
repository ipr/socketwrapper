// socketwrapper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseSocket.h"

int main()
{
	if (startSocket() == false)
	{
		return -1;
	}

	BaseSocket bs; //tmp

	cleanupSocket();
    return 0;
}

