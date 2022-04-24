#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main() {
	WSAData wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	//port
	unsigned short listent_port = 1234;



	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(listent_port);

	bind(server_socket, (SOCKADDR*)&addr, sizeof(addr));

	char buf[256];
	listen(server_socket, sizeof(buf));

	SOCKET client = accept(server_socket, NULL, NULL);

	while (1) {
		int ret = recv(client, buf, sizeof(buf) - 1, 0);
		if (ret <= 0) {
			break;
		}
		buf[ret] = 0;
		printf("%s", buf);
	}

	// pause
	system("pause");

	// close
	closesocket(server_socket);
	WSACleanup();
}