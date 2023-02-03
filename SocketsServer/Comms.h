#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <iostream>


class Comms {
private:

	// Socket for comms
	SOCKET mySocket, acceptSocket;

	// Port comms for data and sockets
	int port = 55555;
	WSADATA wsaData;
	int wsaerr;

	// Info for received message source
	SOCKADDR_STORAGE from;
	int retval, fromlen;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];

public:
	virtual void initialise();
	virtual void createSocket();;
	virtual void bindSocket();
	virtual void listenSocket();
	virtual void connectSocket();
	virtual void accept_socket();
	virtual void serverMessage();
	virtual void clientMessage();
};