#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H
#include <iostream>

using namespace std;

namespace ce {

class CustomException : public exception
{
public:
    CustomException();
    CustomException(char* s);
    char * what();
private:
    char* message = (char *) "My Exception";
};
}

#endif // CUSTOMEXCEPTION_H
