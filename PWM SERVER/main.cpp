#include "include.h"

string key;
string m_data;
string info;


void login(string& answer)
{
	cout << "\nReading Data!\n";
	answer = readData(key);
	if (answer == "") answer = "NODATA";
}

void add_data(string& answer)
{
	cout << "\nAdding data!\n";
	insertData(key, m_data, info);
}

void remove_data(string& answer)
{
	cout << "\nDeleting data!\n";
	deleteData(key, m_data);
}

void delete_acc(string& answer)
{
	cout << "\nDeleting acc!\n";
	deleteAcc(key);
}

void update_data(string& answer)
{
	cout << "\nUpdate data!\n";
	updateData(key, m_data, info);
}

int main()
{
	std::cout << "****************\n*    SERVER    *\n****************\n\n";

	char str[INET_ADDRSTRLEN];

	while (true)
	{
		key = "";
		m_data = "";
		info = "";

		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != NO_ERROR) {
			std::cout << "WSAStartup failed with error: " << iResult << std::endl;
			return 1;
		}

		SOCKET ListenSocket, ClientSocket;
		ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ListenSocket == INVALID_SOCKET) {
			std::cout << "Socket failed with error: " << WSAGetLastError() << std::endl;
			WSACleanup();
			return 1;
		}

		sockaddr_in addrServer;
		addrServer.sin_family = AF_INET;
		inet_pton(AF_INET, "127.0.0.1", &addrServer.sin_addr.s_addr);
		addrServer.sin_port = htons(6666);
		memset(&(addrServer.sin_zero), '\0', 8);

		if (bind(ListenSocket, (SOCKADDR*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR) {
			std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		if (listen(ListenSocket, 5) == SOCKET_ERROR) {
			std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}

		closesocket(ListenSocket);

		int iSendResult;
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			std::string messageINCOMING;
			
			for (int i = 0; i < iResult; i++) messageINCOMING += recvbuf[i];

			cout << "\nINCOMING MESSAGE: " << messageINCOMING;
			std::string ANSWER;
			//DO SOMETHING
			string operation = messageINCOMING.substr(0,10);
			string rawData = messageINCOMING.substr(11);
			int pos = rawData.find("%");
			int posInfo = rawData.find("&");

			string key = rawData.substr(0, pos);
			string m_data = rawData.substr(pos + 1, posInfo-pos-1);
			string info = rawData.substr(posInfo+1);
			cout << "\nOperation:" << operation;
			cout << "\nKey:" << key;
			cout << "\nData:" << m_data;
			cout << "\nInfo:" << info;
			
			if (operation == "LOGIN/////") login(ANSWER);
			if (operation == "DELETE_ACC") delete_acc(ANSWER);
			if (operation == "ADD///////") add_data(ANSWER);
			if (operation == "REMOVE////") remove_data(ANSWER);
			if (operation == "UPDATE////") update_data(ANSWER);

			char tempc[DEFAULT_BUFLEN];
			int i = 0;
			while (ANSWER[i] != '\0') {
				tempc[i] = ANSWER[i];
				i++;
			}
			tempc[i] = '\0';
			const char* sendbuf = tempc;

			iSendResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0);
			if (iSendResult == SOCKET_ERROR) {
				std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			cout << "\nSENDING ANSWER: " << ANSWER << "\n\n";
		}
		else if (iResult == 0)
			std::cout << "Connection closing...\n" << std::endl;
		else {
			std::cout << "Recieve failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

		std::cout << "Connection closing...\n" << std::endl;

		iResult = shutdown(ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

		closesocket(ClientSocket);
		WSACleanup();
	}
	return 0;
}