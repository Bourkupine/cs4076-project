#include "customexception.h"

CustomException::CustomException() {}
CustomException::CustomException(char* s) {
    this->message = s;
}

char* CustomException::what() {
    return message;
}
