#include <iostream>
#include <sstream>
#include "ServerSocket.hpp"
using namespace std;

int main() {
  	ServerSocket server_listener(8888);

  	for(;;) {
	    ServerSocket client_connection;
    	server_listener.acceptConnection(client_connection);
    	cout << "Client IP: " << client_connection.getLastClientIP() << " & " << server_listener.getLastClientIP() << endl << endl;
	
		stringstream recieved;
    	client_connection >> recieved;
    	cout << recieved.str() << endl;
    	cout << recieved.str().length() << endl << endl;

    	client_connection << recieved;
	}
	return 0;	
}