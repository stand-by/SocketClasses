#include "ServerSocket.h"

int sendall(int s, char *buf, int len, int flags);
int recvall(int s, char *buf, int len, int flags);

ServerSocket::ServerSocket(): domain(AF_INET), type(SOCK_STREAM), protocol(IPPROTO_TCP) {
  desc = -1;
  memset(&clientAddress, 0, sizeof(clientAddress));
  memset(&localAddress, 0, sizeof(localAddress));
}
ServerSocket::ServerSocket(const int localPort): domain(AF_INET), type(SOCK_STREAM), protocol(IPPROTO_TCP) {
  if(localPort > 65536 || localPort < 0) throw SocketException("Wrong server port!!!");
  memset(&clientAddress, 0, sizeof(clientAddress));
  memset(&localAddress, 0, sizeof(localAddress));
  localAddress.sin_family = domain;
  localAddress.sin_port = htons(localPort);
  localAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  desc = socket(domain, type, protocol);
  if(desc < 0) throw SocketException("Can not initialize socket!!!");
  if(bind(desc, (struct sockaddr *)&localAddress, sizeof(localAddress)) < 0) throw SocketException("Can not bind the address!!!", this->desc);
  if(listen(desc, 3) < 0) throw SocketException("Can not listen this socket!!!", this->desc);
}
ServerSocket::~ServerSocket() {
  if(desc != -1) close(desc);
}

int ServerSocket::getLocalPort() const {
  int port = ntohs(localAddress.sin_port);
  if(port > 65536 || port < 0)  throw SocketException("Can not convert local port!!!", this->desc);
  return port;
}
int ServerSocket::getLastClientPort() const {
  int port = ntohs(clientAddress.sin_port);
  if(port > 65536 || port < 0)  throw SocketException("Can not convert last client port!!!", this->desc);
  return port;
}
string ServerSocket::getLastClientIP() const {
  if(inet_ntoa(clientAddress.sin_addr) == 0) throw SocketException("Can not convert last client IP!!!", this->desc);
  string ip = inet_ntoa(clientAddress.sin_addr);
  return ip;
}

void ServerSocket::acceptConnection(ServerSocket &tokenSocket) const {
  socklen_t clientSize = sizeof(clientAddress);
  tokenSocket.desc = accept(desc, (struct sockaddr *)&clientAddress, &clientSize);
  if(tokenSocket.desc < 0) throw SocketException("Can not accept client!!!", this->desc);
  tokenSocket.clientAddress = this->clientAddress;
}

void ServerSocket::operator<<(const string &data) const {
  if(sendall(desc, (char *)data.c_str(), data.length(), 0) < 0) throw SocketException("Can not send the data!!!", this->desc);
}
void ServerSocket::operator>>(string &response) const {
  if(recvall(desc, (char *)response.data(), response.size(), 0) < 0) throw SocketException("Can not recieve the data!!!", this->desc);
}

//necessary functions
int sendall(int s, char *buf, int len, int flags) {
    int total = 0;
    int n;
    while(total < len) {
        n = send(s, buf+total, len-total, flags);
        if(n == -1) break;
        total += n;
    }
    return (n==-1 ? -1 : total);
}
int recvall(int s, char *buf, int len, int flags) {
  char *p = buf;
  int n;
  while (len > 0 && (n = recv(s, p, len, flags)) > 0) {
    p += n;
    len =- n;
  }
  if ( len > 0 || n < 0 ) return -1;
  return n;
}
