#include "Comms.h"
#include "WinsockDllNotFoundException.cpp"
#include "InvalidSocketException.cpp"


// Initalises Winsock API and checks if it's found
void Comms::initialise() {
	try {
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		if (wsaerr != 0) {
			throw WinsockDllNotFoundException();
		}
		else {
			cout << "The Winsock dll found!" << endl;
			cout << "The status : " << wsaData.szSystemStatus << endl;
		}
	}
	catch (const WinsockDllNotFoundException& e) {
		cout << "An error occurred while initialising Winsock : " << e.what() << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

// Creates a socket and checks it's created properly
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
		cout << "Error at socket() : " << e.getErrorCode() << endl;
		WSACleanup();
	}
}

// Binds the socket 
void Comms::bindSocket() {
	try {
		sockaddr_in service{};
		service.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
		service.sin_port = htons(port);
		if (bind(mySocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
			throw InvalidSocketException(WSAGetLastError());
		}
		else {
			cout << "bind() is OK!" << endl;
		}
	}
	catch (const InvalidSocketException& e) {
		cout << "Invalid socket created : " << e.what() << " error code: " << e.getErrorCode() << endl;
		closesocket(mySocket);
		WSACleanup();
	}
}

// Socket set to listen for a connection
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
		cout << "Error listening on socket : " << e.what() << " error code : " << e.getErrorCode() << endl;
	}
}

// Connects the socket
void Comms::connectSocket() {
	try {
		sockaddr_in service{};
		service.sin_family = AF_INET;
		InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
		service.sin_port = htons(port);
		if (connect(mySocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
			throw runtime_error("Failed to connect");
		}
	}
	catch (const runtime_error& e) {
		cout << "Client: connect() - " << e.what() << endl;
		WSACleanup();
		return;
	}
	cout << "Client: connect() is OK." << endl;
	cout << "Client: Can start sending and receiving data..." << endl;
}

// Accepts incoming connection
void Comms::accept_socket() {
	try {
		fromlen = sizeof(from);
		acceptSocket = accept(mySocket, (SOCKADDR*)&from, &fromlen);
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
				cout << "getnameinfo failed : " << retval << endl;
				WSACleanup();
				return;
			}
			cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;
		}
	}
	catch (InvalidSocketException& e) {
		cout << "Error: " << e.what() << endl;
		cout << "Error Code : " << e.getErrorCode() << endl;
		WSACleanup();
		return;
	}
}

// Messaging service for server
void Comms::serverMessage() {
	try {
		char buffer[200];
		while (1) {
			int bytesRecv = recv(acceptSocket, buffer, 200, 0);
			if (bytesRecv == 0) {
				throw InvalidSocketException(1);
			}
			else {
				cout << "Received message from client :" << buffer << endl;
			}
			if (strcmp(buffer, "QUIT") == 0) {
				break;
			}
				char buffer2[200];
			cout << "Enter your msg : ";
			cin.getline(buffer2, 200);
			int byteCount1 = send(acceptSocket, buffer2, 200, 0);
			if (byteCount1 == 0) {
				throw InvalidSocketException(2);
			}
			else {
				cout << "Bytes sent " << byteCount1 << endl;
				if (strcmp(buffer2, "QUIT") == 0) {
					break;
				}
			}
		}
	}
	catch (const InvalidSocketException& e) {
		cout << "Error : " << e.what() << " with error code : " << e.getErrorCode() << endl;
	}
}

// Messaging service for client
void Comms::clientMessage() {
	try {
		char buffer[200];
		while (1) {
			cout << "Enter your msg : ";
			cin.getline(buffer, 200);
			int byteCount = send(mySocket, buffer, 200, 0);
			if (byteCount == 0) {
				throw InvalidSocketException(3);
			}
			else {
				cout << "Bytes sent " << byteCount << endl;
				if (strcmp(buffer, "QUIT") == 0) {
					break;
				}
			}
				char buffer1[200];
			int bytesRecv = recv(mySocket, buffer1, 200, 0);
			if (bytesRecv == 0) {
				throw InvalidSocketException(4);
			}
			else {
				cout << "Msg : " << buffer1 << endl;
			}
		}
	}
	catch (const InvalidSocketException& e) {
		cout << "Error : " << e.what() << " with error code : " << e.getErrorCode() << endl;
	}
}
