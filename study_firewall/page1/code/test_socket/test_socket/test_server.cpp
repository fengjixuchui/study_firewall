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
		// 创建套节字
		SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sListen == INVALID_SOCKET)
		{
			printf("Failed socket() \n");
			break;
		} 
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(8080);
		sin.sin_addr.S_un.S_addr = INADDR_ANY; 
		if (::bind(sListen, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			printf("Failed bind() \n");
			break;
		} 
		if (::listen(sListen, 2) == SOCKET_ERROR)
		{
			printf("Failed listen() \n");
			break;
		} 
		sockaddr_in remoteAddr;
		int nAddrLen = sizeof(remoteAddr);
		SOCKET sClient;
		char szText[] = " TCP Server Demo! \r\n";
		while (TRUE)
		{ 
			sClient = ::accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrLen);
			if (sClient == INVALID_SOCKET)
			{
				printf("Failed accept()");
				continue;
			} 
			printf(" 接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr)); 
			::send(sClient, szText, strlen(szText), 0); 
			::closesocket(sClient);
		} 
		::closesocket(sListen);
	} while (false);
    //std::cout << "Hello World!\n";
}

