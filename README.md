# SocketClasses
Simple C++ wrapper classes around UNIX sockets API

This repo provides two C++ classes: ClientSocket and ServerSocket.<br/>
ClientSocket class supposed to be connected through Internet to ServerSocket, which accepts any incoming connections.<br/>
These sockets work under TCP/IP protocol.

### Methods of ClientSocket class:
<ul>
  <li>Constructor accepts server's IP as std::string and server's port as int;
  <li>Methods getServerIP and getServerPort are capable of returning IP and port;
  <li>Operators '<<' and '>>' are able to send and recieve data respectively;
</ul>

### Methods of ServerSocket class:
<ul>
  <li>Constructor accepts only port as int, which will be listened to;
  <li>Method getLocalPort returns port that was specified in constructor;
  <li>Methods getLastClientIP and getLastClientPort are capable of returning last client's IP and port;
  <li>Operators '<<' and '>>' are able to send and recieve data respectively;
</ul>
