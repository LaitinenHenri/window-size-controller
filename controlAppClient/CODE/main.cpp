#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include "Header.h"

#include <iostream>
#include <vector>
#include "windows.h"

#pragma comment(lib, "ws2_32.lib")

/*All commands are one character long so we can easily recognice what command
We are dealing with without havin to break down the message further*/

using namespace std;
string incomingMessage;
string command;
int windowAmmount=0;
string noCommandMsg = "Invalid command on message!";
string returnMsg;
string measurements = "";


void receiveMessages(SOCKET sock) {
	char buf[4096];
	while (true) {
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		if (bytesReceived > 0) {
			incomingMessage = string(buf, 0, bytesReceived);
			if (incomingMessage.substr(12, 2) == "//") {
				command = incomingMessage.substr(14,1);

				//The character "#" ,means an interval window nubmer check
				if (command == "#") {
					//cout << "interval check!" << endl;
					
					enumerateWindows();
					windowAmmount = openWindows.size();
					
					
					//Lets add "#" to the start of the message returning on intervalCheck so the client will know what to expecct
					returnMsg = "//#";
					returnMsg += to_string(windowAmmount);
					int sendResult = send(sock, returnMsg.c_str(), returnMsg.size() + 1, 0);
					//Checking if send fails
					if (sendResult == SOCKET_ERROR) {
						cerr << "Failed to send message to server!" << endl;
						exit;
					}
					
				}//The char "&" means to resize the windows, it is followed by the dimensions
				else if (command == "&") {
					measurements = incomingMessage.substr(15);
					reshapeResizeCommand(measurements);

					returnMsg = "//&";
					int sendResult = send(sock, returnMsg.c_str(), returnMsg.size() + 1, 0);
					if (sendResult == SOCKET_ERROR) {
						cerr << "Failed to send message to server!" << endl;
						break;
					}
				}// If the incoming message is not an valid command or a command line at all
				else {
					int sendResult = send(sock, noCommandMsg.c_str(), noCommandMsg.size() + 1, 0);
					if (sendResult == SOCKET_ERROR) {
						cerr << "Failed to send message to server!" << endl;
						exit;
					}
				}
			}
			else {
				int sendResult = send(sock, noCommandMsg.c_str(), noCommandMsg.size() + 1, 0);
				if (sendResult == SOCKET_ERROR) {
					cerr << "Failed to send message to server!" << endl;
					exit;
				}

			}
		}
	}
}

void main() {



	string ipAddr = "127.0.0.1"; //Server IP
	int port = 54000;// listening port num

	//Init Winsoc
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wResult = WSAStartup(ver, &data);
	if (wResult != 0) {
		cerr << "Cant start winsock" << endl;
		return;
	}

	//create sock
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "cant create socket" << endl;
		WSACleanup();
		return;
	}

	//Filll in a hint struck
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddr.c_str(), &hint.sin_addr);

	//connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Cant connect to server" << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}


	//DO while loop
	char buf[4096];
	int acceptRecv = recv(sock, buf, 4096, 0);
	if (acceptRecv > 0) {
		cout << string(buf, 0, acceptRecv) << endl;
	}
	// Start a thread to continuously receive messages from the server
	thread receiver(receiveMessages, sock);



	// Main loop to handle user input and send messages
	string user_input;
	while(true){
	}

	// Wait for the receiving thread to finish before cleaning up
	receiver.detach();


	//close everything
	closesocket(sock);
	WSACleanup();

}
