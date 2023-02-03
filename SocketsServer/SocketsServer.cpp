#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include "iostream"
#include "Comms.h"
#include "Server.cpp"
#include "Client.cpp"
using namespace std;

// Defining macro to enable server
#define ENABLE_SERVER

int main(int argc, char* argv[]) {

// If server is defined, start the server
#ifdef ENABLE_SERVER
	Server socketsServer;
	socketsServer.start();
#endif

// If client is defined, start the client
#ifdef ENABLE_CLIENT
	Client socketsClient;
	socketsClient.start();
#endif

	return 0;
}



