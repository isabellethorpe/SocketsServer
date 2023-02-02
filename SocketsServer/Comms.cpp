#include "Comms.h"
#include "WinsockDllNotFoundException.cpp"
#include "InvalidSocketException.cpp"


void Comms::initialise() {
	try {
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		if (wsaerr != 0) {
			throw WinsockDllNotFoundException();
		}
		else {
			cout << "The Winsock dll found!" << endl;
			cout << "The status: " << wsaData.szSystemStatus << endl;
		}
	}
	catch (const WinsockDllNotFoundException& e) {
		cout << "An error occurred while initializing Winsock: " << e.what() << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void Comms::createSocket() {
	try {
		mySocket = INVALID_SOCKET;
		mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (mySocket == INVALID_SOCKET) {
			throw InvalidSocketException(WSAGetLastError());
		}
		else {
			cout << "socket() is OK!" << endl;
		}
	}
	catch (const InvalidSocketException& e) {
		cout << "Error at socket(): " << e.getErrorCode() << endl;
		WSACleanup();
	}
}

void Comms::bindSocket() {
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(mySocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(mySocket);
		WSACleanup();
		return;
	}
	else {
		cout << "bind() is OK!" << endl;
	}
}


void Comms::listenSocket() {
	if (listen(mySocket, 1) == SOCKET_ERROR) {
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
		return;
	}
	else {
		cout << "listen() is OK, I'm waiting for connections..." << endl;
	}
}

void Comms::accept_socket() {
	fromlen = sizeof(from);
	acceptSocket = accept(mySocket, (SOCKADDR*)&from, &fromlen);
	// acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		cout << "accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	else {
		cout << "Accepted connection" << endl;
		retval = getnameinfo((SOCKADDR*)&from,
			fromlen,
			hoststr,
			NI_MAXHOST,
			servstr,
			NI_MAXSERV,
			NI_NUMERICHOST | NI_NUMERICSERV);
		if (retval != 0) {
			cout << "getnameinfo failed: " << retval << endl;
			WSACleanup();
			return;
		}
		cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;
	}
}

void Comms::enterMessage() {
	char buffer[200];
	while (1) {
		cout << "Enter your message : ";
		cin.getline(buffer, 200);
		int byteCount = send(mySocket, buffer, 200, 0);
		if (byteCount == 0) {
			cout << "Error" << endl;
		}
		else {
			cout << "Bytes sent : " << byteCount << endl;
			if (strcmp(buffer, "QUIT") == 0) {
				break;
			}
		}
	}
}

void Comms::displayMessage() {
	char buffer1[200] = "Message received";
	int byteCount = send(mySocket, buffer1, 200, 0);
	if (byteCount == 0) {
		cout << "Error" << endl;
	}
	else {
		cout << "Bytes sent : " << byteCount << endl;
	}
}
