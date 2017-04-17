#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include "SocketException.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

class ClientSocket {
  private:
    int desc;
    const int domain;
    const int type;
    const int protocol;
    struct sockaddr_in serverAddress;
  public:
    ClientSocket();
    ClientSocket(const string serverIP, const int serverPort);
    ~ClientSocket();
    string getServerIP() const;
    int getServerPort() const;
    void operator<<(const string &data) const;
    void operator>>(string &response) const;
    void operator<<(const stringstream& stream) const;
};

#endif
