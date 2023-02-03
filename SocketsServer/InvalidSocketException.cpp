#include "Comms.h"
#include <exception>
#include <string>

using namespace std;

class InvalidSocketException : public exception {
private:
    int errorCode;
public:
    // Exception thrown when an invalid socket is created
    InvalidSocketException(int errorCode) : errorCode(errorCode) {}

    const char* what() const throw() {
        return "Invalid socket created";
    }

    int getErrorCode() const {
        return errorCode;
    }
};
