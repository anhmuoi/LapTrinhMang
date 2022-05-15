#include <stdio.h>
#include <winsock.h>
#include <string.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable : 4996)
int main() {

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);

	bind(listener, (sockaddr*)&addr, sizeof(addr));

	listen(listener, 5);

	SOCKET client = accept(listener, NULL, NULL);

	send(client, "Please type username and password to login: ", 45, 0);

	char buf[1024];

	bool isLoggedIn = false;

	while (1) {
		int ret = recv(client, buf, sizeof(buf) - 1, 0);

		if (ret == SOCKET_ERROR) {
			break;
		}

		buf[ret - 1] = 0;

		if (!isLoggedIn) {

			FILE* f = fopen("C:\\Users\\CHINH.LT198209\\source\\repos\\ltm\\3\\Bai2\\account.txt", "r");

			char account[100];

			while (!feof(f)) {
				fgets(account, sizeof(account), f);

				account[strlen(account) - 1] = account[strlen(account) - 1] == '\n' ? 0 : account[strlen(account) - 1];

				if (strcmp(buf, account) == 0) {
					isLoggedIn = true;
					send(client, "Login successful!\n", 19, 0);
					break;
				}
			}

			if (!isLoggedIn)
				send(client, "Login fail!\n", 13, 0);

			fclose(f);
		}
		else {
			strcat(buf, " > C:\\Users\\CHINH.LT198209\\source\\repos\\ltm\\3\\Bai2\\out.txt");

			system(buf);

			send(client, "Success! See response at directory C:\\Users\\CHINH.LT198209\\source\\repos\\ltm\\3\\Bai2\\out.txt\n", 47, 0);
		}

	}
}