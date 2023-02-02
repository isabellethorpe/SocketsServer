#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include "iostream"
#include "Comms.h"
#include "Server.cpp"
#include "Client.cpp"
using namespace std;


#define ENABLE_SERVER

int main(int argc, char* argv[]) {


#ifdef ENABLE_SERVER
	Server socketsServer;
	socketsServer.start();
#endif


#ifdef ENABLE_CLIENT
	cout << "Starting client..." << endl;
	socketsServer.initialise();
	socketsServer.createSocket();
	socketsServer.bindSocket();
	socketsServer.listenSocket();
	socketsServer.accept_socket();
	socketsServer.enterMessage();
	socketsServer.displayMessage();
#endif

	return 0;
}












//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <tchar.h>
//#include "iostream"
//#include "Comms.cpp"
//
//using namespace std;
//
//
//class Server : public Comms {
//
//	SOCKET mySocket, acceptSocket;
//
//	int main(int argc, char* argv[]) {
//		Server socketsServer;
//
//		socketsServer.initialise();
//		socketsServer.createSocket();
//		socketsServer.listenSocket();
//		socketsServer.accept_socket();
//		socketsServer.enterMessage();
//		socketsServer.displayMessage();
//
//		return 0;
//	}
//};











//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <tchar.h>
//#include "iostream"
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	// STARTUP - LOADING DLL
//	SOCKET serverSocket, acceptSocket;
//	int port = 55555;
//	WSADATA wsaData;
//	int wsaerr;
//
//	// newly added
//	SOCKADDR_STORAGE from;
//	int retval, fromlen;
//	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];
//
//
//	WORD wVersionRequested = MAKEWORD(2, 2);
//	wsaerr = WSAStartup(wVersionRequested, &wsaData);
//	if (wsaerr != 0) {
//		cout << "The Winsock dll not found!" << endl;
//		return 0;
//	}
//	else {
//		cout << "The Winsock dll found!" << endl;
//		cout << "The status: " << wsaData.szSystemStatus << endl;
//	}
//
//
//
//
//
//	// CREATE SOCKET
//	serverSocket = INVALID_SOCKET;
//	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (serverSocket == INVALID_SOCKET) {
//		cout << "Error at socket(): " << WSAGetLastError() << endl;
//		WSACleanup();
//		return 0;
//	}
//	else {
//		cout << "socket() is OK!" << endl;
//	}
//
//	// BIND SOCKET TO SERVERS UP ADDRESS AND VALID PORT
//	sockaddr_in service;
//	service.sin_family = AF_INET;
//	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
//	service.sin_port = htons(port);
//	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
//		cout << "bind() failed: " << WSAGetLastError() << endl;
//		closesocket(serverSocket);
//		WSACleanup();
//		return 0;
//	}
//	else {
//		cout << "bind() is OK!" << endl;
//	}
//
// 
// 	void bindSocket() {
//
//	// PLACING INTO LISTENING STATE
//
//	if (listen(serverSocket, 1) == SOCKET_ERROR)
//		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
//	else
//		cout << "listen() is OK, I'm waiting for connections..." << endl;
//
//	// WAITING FOR CLIENT CONNECTION, RETURNS NEW SOCKET
//	// THAT IS CONNECTED TO THE CLIENT
//
//	// newly added
//	fromlen = sizeof(from);
//	acceptSocket = accept(serverSocket, (SOCKADDR*)&from, &fromlen);
//	// acceptSocket = accept(serverSocket, NULL, NULL);
//	if (acceptSocket == INVALID_SOCKET) {
//		cout << "accept failed: " << WSAGetLastError() << endl;
//		WSACleanup();
//		return -1;
//	}
//
//
//	cout << "Accepted connection" << endl;
//	// newly added
//	retval = getnameinfo((SOCKADDR*)&from,
//		fromlen,
//		hoststr,
//		NI_MAXHOST,
//		servstr,
//		NI_MAXSERV,
//		NI_NUMERICHOST | NI_NUMERICSERV);
//	if (retval != 0) {
//		cout << "getnameinfo failed: " << retval << endl;
//		WSACleanup();
//		return -1;
//	}
//
//	cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;
//
//	char buffer[200];
//	while(1) {
//		int bytesRecv = recv(acceptSocket, buffer, 200, 0);
//		if (bytesRecv == 0) {
//			// return 1 and crash out the programme
//			cout << "Error" << endl;
//			return -1;
//		}
//		else {
//			/*cout << "Bytes received : " << bytesRecv << endl;*/
//			cout << "Message : " << buffer << endl;
//		}
//
//		if (strcmp(buffer, "SHUTDOWN") == 0) {
//			break;
//		}
//
//		char buffer1[200] = "Message received";
//		int byteCount = send(acceptSocket, buffer1, 200, 0);
//		if (byteCount == 0) {
//			cout << "Error" << endl;
//		}
//		else {
//			cout << "Bytes sent : " << byteCount << endl;
//		}
//
//
//		char buffer2[200];
//		cout << "Enter your message : ";
//		cin.getline(buffer2, 200);
//		int byteCount1 = send(acceptSocket, buffer2, 200, 0);
//		if (byteCount1 == 0) {
//			cout << "Error" << endl;
//		}
//		else {
//			cout << "Bytes sent : " << byteCount1 << endl;
//			if (strcmp(buffer2, "SHUTDOWN") == 0) {
//				break;
//			}
//		}
//
//	}
//
//	system("pause");
//	WSACleanup();
//
//	return 0;
//
//}
//
