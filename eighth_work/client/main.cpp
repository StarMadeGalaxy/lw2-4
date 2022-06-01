#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <bitset>
#include <string>

#define DEFAULT_PORT 80
#define DEFAULT_ADDR "127.0.0.1"
#define BUFFER_SIZE 512

#pragma comment(lib, "Ws2_32.lib")	// only for windows compilers

	
int main(int argc, const char* argv[])
{
	std::cout << "[CLIENT]" << std::endl;
	std::cout << "[IP]: " << DEFAULT_ADDR << std::endl;
	std::cout << "[PORT]: " << htons(DEFAULT_PORT) << std::endl << std::endl;


	WSADATA	wsaData = WSADATA();

	int iResult = int();

	// The WSAStartup function is called to initiate use of WS2_32.dll.
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return EXIT_FAILURE;
	}

	/*std::string BinDefaultPort = std::bitset<16>(DEFAULT_PORT).to_string();
	std::string HtonsBinDefaultPort = std::bitset<16>(htons(DEFAULT_PORT)).to_string();
	std::cout << std::endl << BinDefaultPort.substr(0, 8) << ' ' << BinDefaultPort.substr(8, BinDefaultPort.length());
	std::cout << std::endl;
	std::cout << HtonsBinDefaultPort.substr(0, 8) << ' ' << HtonsBinDefaultPort.substr(8, HtonsBinDefaultPort.length());
	std::cout << std::endl;*/

	struct sockaddr_in info = sockaddr_in();
	info.sin_family = AF_INET;
	info.sin_port = htons(DEFAULT_PORT); // host-to-network short
	inet_pton(AF_INET, DEFAULT_ADDR, &info.sin_addr);


	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << "Socket creation failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return EXIT_FAILURE;
	}

	iResult = connect(ConnectSocket, (sockaddr*)&info, static_cast<int>(sizeof(info)));
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Socket connection failed: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
		WSACleanup();
		return EXIT_FAILURE;
	}

	int recieve_buffer_length = BUFFER_SIZE;

	char recieve_buffer[BUFFER_SIZE];
	char send_buffer[BUFFER_SIZE];

	
	while (1)
	{
		std::cout << "\nEnter a message: ";
		std::cin.getline(send_buffer, BUFFER_SIZE);

		iResult = send(ConnectSocket, send_buffer, static_cast<int>(strlen(send_buffer)), 0);

		if (send_buffer[0] == '-')
		{
			std::cout << "\nClient disconnecting...\n";
			break;
		}

		if (iResult == SOCKET_ERROR) {
			printf("Send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		else 
		{
			std::cout << "Bytes Sent: " << iResult << std::endl;
		}

		iResult = recv(ConnectSocket, recieve_buffer, recieve_buffer_length, 0);

		if (recieve_buffer[0] == '-')
		{
			std::cout << "\nServer is shutting down...\n";
			break;
		}

		if (iResult > 0)
		{
			std::cout << "\nBytes received: " << iResult << std::endl;
			std::cout << "Text from a server: ";
			for (int i = 0; i < iResult; i++)
				std::cout << recieve_buffer[i];
			std::cout << std::endl;

		}
		else if (iResult < 0)
		{
			std::cout << "recv failed: " << WSAGetLastError() << std::endl;
		}
	}

	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	closesocket(ConnectSocket);
	WSACleanup();

	return EXIT_SUCCESS;
}