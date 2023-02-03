#include "Comms.h"
#include <iostream>

using namespace std;

class Server : public Comms {
public:
	// Starts the server process
	void start() {

		cout << "Starting server..." << endl;
		Comms::initialise();
		Comms::createSocket();
		Comms::bindSocket();
		Comms::listenSocket();
		Comms::accept_socket();
		Comms::serverMessage();
	}
};

