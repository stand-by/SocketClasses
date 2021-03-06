#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include "SocketException.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

class ServerSocket {
  private:
    int desc;
    const int domain;
    const int type;
    const int protocol;
    struct sockaddr_in localAddress;
    struct sockaddr_in clientAddress;
  public:
    ServerSocket();
    ServerSocket(const int localPort);
    ~ServerSocket();
    int getLocalPort() const;
    int getLastClientPort() const;
    string getLastClientIP() const;
    void acceptConnection(ServerSocket &tokenSocket) const;
    void operator<<(const string &data) const;
    void operator>>(string &response) const;
    void operator<<(const stringstream &data) const;
    void operator>>(stringstream &response) const;
};

#endif
