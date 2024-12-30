#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <string>
#include <sstream>

using namespace std;

void main() {
	//Initializing winsock
	WSADATA wsData;
	WORD version = MAKEWORD(2, 2);

	int wsok = WSAStartup(version, &wsData);
	if (wsok != 0) {
		cerr << "Cant connect to winsock! Quitting ´" << endl;
		return;
	}


	// creating a socket
	SOCKET listeningSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listeningSock == INVALID_SOCKET) {
		cerr << "cant create listening socket!" << endl;
		return;
	}

	//binding socket
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(54000);
	address.sin_addr.S_un.S_addr = INADDR_ANY;



	bind(listeningSock, (sockaddr*)&address, sizeof(address));

	//Set as listening
	listen(listeningSock, SOMAXCONN);
	
	fd_set master;
	FD_ZERO(&master);
	
	FD_SET(listeningSock, &master);

	while (true) {
		fd_set masterCopy = master;

		int socketCount = select(0, &masterCopy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++) {
			SOCKET sock = masterCopy.fd_array[i];
			if (sock == listeningSock) {
				//Accept a new connection
				//SOCKET client = accept(listeningSock, nullptr, nullptr);
				SOCKET client = accept(listeningSock, nullptr, nullptr);

				//ADd the new connection to list of connected clients (materCopy & master)
				FD_SET(client, &master);
				//Send confirmation
				string confirmation = "connection accepted\r\n";
				send(client, confirmation.c_str(), confirmation.size() + 1, 0);


			}
			else {

				char buf[4096];
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived <= 0) {
					//Drop client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else {
					for (int i = 0; i < master.fd_count; ++i) {
						SOCKET outSock = master.fd_array[i];
						if (outSock != listeningSock && outSock != sock) {
							ostringstream ss;
							ss << "SOCKET #" << sock << ":" << buf;
							string strOut = ss.str();
							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
				//accept new message
				//send message to other client, NOT LISTENIGN SOCKET!
			}
		}
	}

	// shutting winsock down
	WSACleanup();
	system("pause");
}




/*
	//Wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSock = accept(listeningSock, (sockaddr*)&client, &clientSize);
	if (clientSock == INVALID_SOCKET) {
		cerr << "invalid client socket!" << endl;
		return;
	}

	char host[NI_MAXHOST];  //Clients remote name
	char service[NI_MAXSERV];  // Service (i.e. port ) client is connected on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {

		cout << host << " connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}


	//Closing listening socket
	closesocket(listeningSock);

	//while loop
	char buf[4096];

	string message = "";
	string command = "";

	while (true) {
		ZeroMemory(buf, 4096);

		int bytesReceived = recv(clientSock, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR) {
			cerr << "ERROR IN RECV()" << endl;
			break;
		}
		if (bytesReceived == 0) {
			cout << "Client disconnected " << endl;
			break;
		}
		message.append(buf, bytesReceived);
		command = message.substr(0, 4);

		cout << string(buf, 0, bytesReceived) << endl;;

		send(clientSock, buf, bytesReceived + 1, 0);



	}*/


	//closing socket
	//closesocket(clientSock);