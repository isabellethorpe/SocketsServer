#include "Comms.h"
#include <exception>
#include <string>

using namespace std;

class WinsockDllNotFoundException : public runtime_error {
public:
    // Exception is thrown when Winsock cannot be found
    WinsockDllNotFoundException() : runtime_error("The Winsock dll not found!") {}
};