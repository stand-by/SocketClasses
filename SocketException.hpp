#ifndef SOCKETEXCEPTION_HPP
#define SOCKETEXCEPTION_HPP

#include <exception>
#include <iostream>
using namespace std;

class SocketException : public exception {
  private:
    int desc;
    string errorMessage;
  public:
    SocketException(const string msg): errorMessage(msg), desc(-1) {}
    SocketException(const string msg, const int sock): errorMessage(msg), desc(sock) {}
    ~SocketException() throw() {}
    void setSocketDesc(const int sock) {desc = sock;}
    int getSocketDesc() const {return desc;}
    const char* what() const throw() {return errorMessage.c_str();}
};

#endif
