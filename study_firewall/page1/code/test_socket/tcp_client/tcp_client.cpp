#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "WS2_32")	// 链接到WS2_32.lib
int init_sock(BYTE minorVer = 2, BYTE majorVer = 2) {
	// 初始化WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(minorVer, majorVer);
	if (::WSAStartup(sockVersion, &wsaData) != 0)
	{
		return -1;
	}
	return 0;
}
void close_sock() {
	::WSACleanup();
}

int main()
{
	do {
		if (init_sock(2, 2) != 0) {
			break;
		}
		SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET)
		{
			printf(" Failed socket() \n");
			break;
		}
		sockaddr_in servAddr;
		servAddr.sin_family = AF_INET;
		servAddr.sin_port = htons(8080); 
		servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		{
			printf(" Failed connect() \n");
			break;
		} 
		char buff[256];
		int nRecv = ::recv(s, buff, 256, 0);
		if (nRecv > 0)
		{
			buff[nRecv] = '\0';
			printf(" 接收到数据：%s", buff);
		} 
		::closesocket(s);
	} while (false);
	return 0;
    //std::cout << "Hello World!\n";
}
