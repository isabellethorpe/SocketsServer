#include "Comms.h"
#include <exception>
#include <string>

using namespace std;

class InvalidSocketException : public exception {
private:
    int errorCode;
public:
    InvalidSocketException(int errorCode) : errorCode(errorCode) {}

    const char* what() const throw() {
        return "Invalid socket created";
    }

    int getErrorCode() const {
        return errorCode;
    }
};
