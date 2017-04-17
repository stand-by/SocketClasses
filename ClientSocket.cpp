#include "ClientSocket.hpp"

int sendall(int s, char *buf, int len, int flags);
int recvall(int s, char *buf, int len, int flags);

ClientSocket::ClientSocket(): domain(AF_INET), type(SOCK_STREAM), protocol(IPPROTO_TCP) {
  desc = -1;
  memset(&serverAddress, 0, sizeof(serverAddress));
}
ClientSocket::ClientSocket(const string serverIP, const int serverPort): domain(AF_INET), type(SOCK_STREAM), protocol(IPPROTO_TCP) {
  if(serverPort > 65536 || serverPort < 0) throw SocketException("Wrong server port!!!");
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = domain;
  serverAddress.sin_port = htons(serverPort);
  int res = inet_aton(serverIP.c_str(),  &serverAddress.sin_addr);
  if(res == 0) throw SocketException("Wrong server IP!!!");
  desc = socket(domain, type, protocol);
  if(desc < 0) throw SocketException("Can not initialize socket!!!");
  if(connect(desc, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) throw SocketException("Can not connect to server!!!", this->desc);
}
ClientSocket::~ClientSocket() {
  if(desc != -1) close(desc);
}

string ClientSocket::getServerIP() const {
  if(inet_ntoa(serverAddress.sin_addr) == 0) throw SocketException("Can not convert server IP!!!", this->desc);
  string ip = inet_ntoa(serverAddress.sin_addr);
  return ip;
}
int ClientSocket::getServerPort() const {
  int port = ntohs(serverAddress.sin_port);
  if(port > 65536 || port < 0)  throw SocketException("Can not convert server port!!!", this->desc);
  return port;
}

void ClientSocket::operator<<(const string &data) const {
  if(sendall(desc, (char *)data.c_str(), data.length(), 0) < 0) throw SocketException("Can not send the data!!!", this->desc);
}
void ClientSocket::operator>>(string &response) const {
  if(recvall(desc, (char *)response.data(), response.size(), 0) < 0) throw SocketException("Can not recieve the data!!!", this->desc);
}
void ClientSocket::operator<<(const stringstream& stream) const {
  if(sendall(desc, (char *)stream.str().c_str(), stream.str().length(), 0) < 0) throw SocketException("Can not send the data!!!", this->desc);
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
