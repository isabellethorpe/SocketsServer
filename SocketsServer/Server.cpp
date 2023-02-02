#include "Comms.h"

using namespace std;

class Server : public Comms {
public:
	void start() {

		cout << "Starting server..." << endl;
		Comms::initialise();
		Comms::createSocket();
		Comms::bindSocket();
		Comms::listenSocket();
		Comms::accept_socket();
		Comms::enterMessage();
		Comms::displayMessage();
	}
};

