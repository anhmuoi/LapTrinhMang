#include <stdio.h>
#include <WinSock2.h>
#include <cstring>
#include <string>
#include <ws2tcpip.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
#pragma warning(disable:4700)

int main() {

	char target_ip[20] = "127.0.0.1";

	// port 
	unsigned short target_port = 1234;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKADDR_IN addr;

	addr.sin_addr.s_addr = inet_addr(target_ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(target_port);



	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int ret = connect(client_socket, (SOCKADDR*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR) {
		printf("Loi ket noi\n");
		return 0;
	};

	char client_info[100] = "";

	// get name and print name of computer
	CHAR ComputerName[50];
	printf("abc");
	DWORD   size = 50;
	printf("abc");
	if (GetComputerNameA(ComputerName, &size)) {
		printf("abc");
		strcat(client_info, "Computer Name: ");
		strcat(client_info, ComputerName);
		strcat(client_info, "\n");
	};

	//printf("abc");

	// get drive name 
	CHAR DriveName[32];
	if (GetLogicalDriveStringsA(256, DriveName)) {
		strcat(client_info, "Drive Name: ");
		strcat(client_info, DriveName);
		strcat(client_info, "\n");
	};

	// get free space
	LPCSTR root = "C:\\"; // root

	DWORD sectorsPerCluster;
	DWORD bytesPerSector;
	DWORD numberOfFreeClusters;
	DWORD totalNumberOfClusters;

	if (GetDiskFreeSpaceA(root, &sectorsPerCluster, &bytesPerSector, &numberOfFreeClusters, &totalNumberOfClusters)) {

		long long free_space = (long long)bytesPerSector * sectorsPerCluster * numberOfFreeClusters;

		std::string s = (std::to_string(free_space));
		const char* freespace = s.c_str();

		strcat(client_info, "Free Space: ");
		strcat(client_info, freespace);
		strcat(client_info, " Byte\n");
	};


	// send 
	send(client_socket, client_info, strlen(client_info), 0);

	// close 
	closesocket(client_socket);
	WSACleanup();
}