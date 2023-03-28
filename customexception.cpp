#include "customexception.h"

CustomException::CustomException() {}
CustomException::CustomException(char* s) {
    this->message = s;
}

char* CustomException::what() {
    return (char*) message;
}


/*
 * try {
 * throw CustomException();
 * } catch(CustomException ce) {
 * cout << ce.what();
 * }
 */
