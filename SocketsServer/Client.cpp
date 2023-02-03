#include "Comms.h"

using namespace std;

class Client : public Comms {
public:
	void start() {

		cout << "Starting client..." << endl;
		Comms::initialise();
		Comms::createSocket();
		Comms::connectSocket();
		Comms::clientMessage();
	}
};

