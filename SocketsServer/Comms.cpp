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

//void Comms::bindSocket() {
//	try {
//		sockaddr_in service{};
//		service.sin_family = AF_INET;
//		InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
//		service.sin_port = htons(port);
//		if (bind(mySocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
//			throw InvalidSocketException(WSAGetLastError());
//		}
//		else {
//			cout << "bind() is OK!" << endl;
//		}
//	}
//	catch (const InvalidSocketException& e) {
//		cout << "Invalid socket created: " << e.what() << " error code: " << e.getErrorCode() << endl;
//		closesocket(mySocket);
//		WSACleanup();
//	}
//}

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
	try {
		if (listen(mySocket, 1) == SOCKET_ERROR) {
			throw InvalidSocketException(WSAGetLastError());
		}
		else {
			cout << "listen() is OK, I'm waiting for connections..." << endl;
		}
	}
	catch (const InvalidSocketException& e) {
		cout << "Error listening on socket: " << e.what() << " error code: " << e.getErrorCode() << endl;
	}
}



void Comms::connectSocket() {
	sockaddr_in service{};
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (connect(mySocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return;
	}
	else {
		cout << "Client: connect() is OK." << endl;
		cout << "Client: Can start sending and receiving data..." << endl;
	}
}


void Comms::accept_socket() {
	try {
		fromlen = sizeof(from);
		acceptSocket = accept(mySocket, (SOCKADDR*)&from, &fromlen);
		// acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET) {
			throw InvalidSocketException(WSAGetLastError());
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
	catch (InvalidSocketException& e) {
		cout << "Error: " << e.what() << endl;
		cout << "Error Code: " << e.getErrorCode() << endl;
		WSACleanup();
		return;
	}
}

void Comms::enterMessage() {
	try {
		char buffer[200];
		while (1) {
			cout << "Enter your message : ";
			cin.getline(buffer, 200);
			int byteCount = send(mySocket, buffer, 200, 0);
			if (byteCount == SOCKET_ERROR) {
				throw InvalidSocketException(WSAGetLastError());
			}
			cout << "Bytes sent : " << byteCount << endl;
			if (strcmp(buffer, "QUIT") == 0) {
				break;
			}
		}
	}
	catch (const InvalidSocketException& e) {
		cout << e.what() << endl;
		cout << "Error code: " << e.getErrorCode() << endl;
	}
}

void Comms::displayMessage() {
	try {
		char buffer1[200] = "Message received";
		int byteCount = send(mySocket, buffer1, 200, 0);
		if (byteCount == SOCKET_ERROR) {
			throw InvalidSocketException(WSAGetLastError());
		}
		cout << "Bytes sent : " << byteCount << endl;
	}
	catch (const InvalidSocketException& e) {
		cout << e.what() << endl;
		cout << "Error code: " << e.getErrorCode() << endl;
	}
}
