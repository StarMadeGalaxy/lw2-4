#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <bitset>
#include <cstring>
#include <cstdio>

#define DEFAULT_PORT 80
#define DEFAULT_ADDR "127.0.0.1"
#define BUFFER_SIZE 512

#pragma comment(lib, "Ws2_32.lib")	// only for windows compilers


int main(int argc, const char* argv[])
{
	std::cout << "[SERVER]" << std::endl;
	std::cout << "[IP]: " << DEFAULT_ADDR << std::endl;
	std::cout << "[PORT]: " << htons(DEFAULT_PORT) << std::endl << std::endl;


	WSADATA	wsaData = WSADATA();

	int iResult = int();
	int iSendResult = int();

	// The WSAStartup function is called to initiate use of WS2_32.dll.
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return EXIT_FAILURE;
	}

	struct sockaddr_in info = sockaddr_in();
	info.sin_family = AF_INET;
	info.sin_port = htons(DEFAULT_PORT); // host-to-network short
	inet_pton(AF_INET, DEFAULT_ADDR, &info.sin_addr);

	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ListenSocket == INVALID_SOCKET) {
		std::cout << "Socket creation failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return EXIT_FAILURE;
	}

	iResult = bind(ListenSocket, (sockaddr*)&info, static_cast<int>(sizeof(info)));
	if (iResult == SOCKET_ERROR) {
		printf("Bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}


	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	SOCKET ClientSocket = INVALID_SOCKET;

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Client connected with socket: " << ClientSocket << std::endl;
	}

	closesocket(ListenSocket);

	int recieve_buffer_length = BUFFER_SIZE;

	char recieve_buffer[BUFFER_SIZE];
	char send_buffer[BUFFER_SIZE];
	

	while (1)
	{
		iResult = recv(ClientSocket, recieve_buffer, recieve_buffer_length, 0);

		if (iResult < 0)
		{
			std::cout << "recv failed:" << WSAGetLastError();
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
		else if (iResult > 0)
		{
			std::cout << "\nBytes received: " << iResult << std::endl;
			std::cout << "Text from a client: ";
			for (int i = 0; i < iResult; i++)
				std::cout << recieve_buffer[i];
			std::cout << std::endl;
		}

		if (recieve_buffer[0] == '-')
		{
			std::cout << "\nClient disconnected from the server. [SOCKET]: " << ClientSocket << std::endl;
			break;
		}

		std::cout << "\nEnter a message: ";
		std::cin.getline(send_buffer, BUFFER_SIZE);
		iSendResult = send(ClientSocket, send_buffer, static_cast<int>(strlen(send_buffer)), 0);


		if (iSendResult == SOCKET_ERROR) {
			std::cout << "Send failed:" << WSAGetLastError() << std::endl;
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

		std::cout << "Bytes sent: " << iSendResult << std::endl << std::endl;

		if (send_buffer[0] == '-')
		{
			std::cout << "Server closing connection..." << std::endl;
			break;
		}
	} 

	iResult = shutdown(ClientSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}
		
	closesocket(ClientSocket);
	WSACleanup();

	return EXIT_SUCCESS;
}