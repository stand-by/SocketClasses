#include <iostream>
#include <sstream>
#include "ClientSocket.hpp"
using namespace std;

int main(int argc, char const *argv[]) {
	ClientSocket server_connection("127.0.0.1", 8888);
	
	int size = std::stoi(argv[1]);
	stringstream stream;
	
	stream << "1";
    for(int i=1; i < size-1; ++i)
      stream << i%10;
    stream << "0";
	
    cout << "Sending Data with size = " << stream.str().length() << endl;
    cout << stream.str() << endl << endl;

	server_connection << stream;

	stringstream respond;
	server_connection >> respond;

	cout << respond.str() << endl;
    cout << "Recieved Data with size = " << respond.str().length() << endl;
	return 0;	
}