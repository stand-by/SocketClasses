#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "SocketException.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
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
};

#endif
