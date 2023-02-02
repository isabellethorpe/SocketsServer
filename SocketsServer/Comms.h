#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include "iostream"

//using namespace std;


class Comms {
private:

	SOCKET mySocket, acceptSocket;

	int port = 55555;
	WSADATA wsaData;
	int wsaerr;

	SOCKADDR_STORAGE from;
	int retval, fromlen;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];

public:
	virtual void initialise();
	virtual void createSocket();
	virtual void bindSocket();
	virtual void listenSocket();
	virtual void accept_socket();
	virtual void enterMessage();
	virtual void displayMessage();
};