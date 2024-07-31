#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#include <atomic>
#include <mutex>
#include <iostream>
using namespace std;
// ����
// 1) ���ο� ���� ���� (socket)
// 2) ���Ͽ� �ּ�/��Ʈ ��ȣ ���� (bind)
// 3) ���� �� ��Ű�� (listen)
// 4) �մ� ���� (accept)
// 5) Ŭ��� ���

using int32 = __int32;

int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 1) ���� ����
	// ad : Address Family (AF_INET = IPv4, AF_INET6 = IPv6)
	// type : TCP(SOCK_STREAM) vs UDP(SOCK_DGRAM)
	// protocol : 0
	// return : descriptor
	//int32 errorCode = ::WSAGetLastError();
	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == 0)
		return 0;

	// 2) �ּ�/��Ʈ ��ȣ ���� (bind)
	// ������ ��������? (IP�ּ� + Port) -> XX ����Ʈ YY ȣ
	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // �ƹ� IP��
	serverAddr.sin_port = ::htons(7777); // 80 : HTTP

	// host to network short
	// Little-Endian vs Big-Endian
	// ex) 0x12345678 4����Ʈ ����
	// low [0x78][0x56][0x34][0x12] high < little
	// low [0x12][0x34][0x56][0x78] high < big = network

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	// 3) ���� ���� (listen)
	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	// 4) �մ� ���� (accept)
	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
			return 0;

		// �մ� ����!
		char ip[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));
		cout << "Client Connected! IP = " << ip << endl;

		// 5) TODO
		while (true)
		{
			char recvBuffer[100];
			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen <= 0)
				return 0;

			cout << "Recv Data : " << recvBuffer << endl;
			cout << "Recv Data Len : " << recvLen << endl;

			int32 resultCode = ::send(clientSocket, recvBuffer, recvLen, 0);
			if (resultCode == SOCKET_ERROR)
				return 0;
		}
	}

	::closesocket(listenSocket);
	::WSACleanup();
}