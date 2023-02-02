#include "Comms.h"
#include <exception>
#include <string>

using namespace std;

class WinsockDllNotFoundException : public runtime_error {
public:
    WinsockDllNotFoundException() : runtime_error("The Winsock dll not found!") {}
};