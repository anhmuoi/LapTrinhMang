#include <stdio.h>

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

DWORD WINAPI DataThread(LPVOID lpParam)
{
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(2561);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    SOCKET dataCon = accept(listener, NULL, NULL);

    char buf[256];
    int ret;
    while (1)
    {
        ret = recv(dataCon, buf, sizeof(buf), 0);
        if (ret <= 0) {
            break;
        }
        buf[ret] = 0;
        printf("%s", buf);
    }
}


int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(21);

    int ret = connect(client_sock, (SOCKADDR*)&addr, sizeof(addr));

    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Connection fail - %d\n", ret);
        return 1;
    }

    char sendbuf[256],sendcmd[256];
    char buf[256];

    ret = recv(client_sock, buf, sizeof(buf) - 1, 0);
    if (ret > 0) {
        buf[ret] = 0;
        printf("%s\n", buf);
    }

    while (1) {
        char user[32], password[32];
        printf("\nNhap username:");
        scanf("%s", &user);

        if (strcmp(user, "exit") == 0) {
            closesocket(client_sock);
            WSACleanup();
            return 1;
        }
        printf("\nNhap password:");
        scanf("%s", &password);

        sprintf(sendcmd, "USER %s\r\n", user);
        send(client_sock, sendcmd, strlen(sendcmd), 0);

        ret = recv(client_sock, buf, sizeof(buf), 0);
        /*buf[ret] = 0;
        printf("%s", buf);*/

        sprintf(sendcmd, "PASS %s\r\n", password);
        send(client_sock, sendcmd, strlen(sendcmd), 0);

        ret = recv(client_sock, buf, sizeof(buf), 0);
        buf[ret] = 0;
        printf("%s", buf);

        // xu ly ket qua lenh PASS
        if (strncmp(buf, "230", 3) == 0) {
            printf("\nDang nhap thanh cong");
            break;
        }
        else {
            printf("\nDang nhap that bai! Hay dang nhap lai");
        }
    }

    // Gui lenh list

    // Gui lenh port
    sprintf(sendcmd, "PORT 127,0,0,1,10,1\r\n");
    send(client_sock, sendcmd, strlen(sendcmd), 0);

    ret = recv(client_sock, buf, sizeof(buf), 0);
    buf[ret] = 0;
    printf("%s", buf);

    CreateThread(0, 0, DataThread, 0, 0, 0);

    // gui lenh LIST
    strcpy(sendcmd, "LIST\r\n");
    send(client_sock, sendcmd, strlen(sendcmd), 0);

    ret = recv(client_sock, buf, sizeof(buf), 0);
    buf[ret] = 0;
    printf("%s", buf);

    while (1) 
    {

    }

  closesocket(client_sock);
    WSACleanup();
}

#include <stdio.h>

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

DWORD WINAPI DataThread(LPVOID lpParam)
{
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(2561);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);

    SOCKET dataCon = accept(listener, NULL, NULL);

    char buf[256];
    int ret;
    while (1)
    {
        ret = recv(dataCon, buf, sizeof(buf), 0);
        if (ret <= 0) {
            break;
        }
        buf[ret] = 0;
        printf("%s", buf);
    }
}


int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(21);

    int ret = connect(client_sock, (SOCKADDR*)&addr, sizeof(addr));

    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Connection fail - %d\n", ret);
        return 1;
    }

    char sendbuf[256],sendcmd[256];
    char buf[256];

    ret = recv(client_sock, buf, sizeof(buf) - 1, 0);
    if (ret > 0) {
        buf[ret] = 0;
        printf("%s\n", buf);
    }

    while (1) {
        char user[32], password[32];
        printf("\nNhap username:");
        scanf("%s", &user);

        if (strcmp(user, "exit") == 0) {
            closesocket(client_sock);
            WSACleanup();
            return 1;
        }
        printf("\nNhap password:");
        scanf("%s", &password);

        sprintf(sendcmd, "USER %s\r\n", user);
        send(client_sock, sendcmd, strlen(sendcmd), 0);

        ret = recv(client_sock, buf, sizeof(buf), 0);
        /*buf[ret] = 0;
        printf("%s", buf);*/

        sprintf(sendcmd, "PASS %s\r\n", password);
        send(client_sock, sendcmd, strlen(sendcmd), 0);

        ret = recv(client_sock, buf, sizeof(buf), 0);
        buf[ret] = 0;
        printf("%s", buf);

        // xu ly ket qua lenh PASS
        if (strncmp(buf, "230", 3) == 0) {
            printf("\nDang nhap thanh cong");
            break;
        }
        else {
            printf("\nDang nhap that bai! Hay dang nhap lai");
        }
    }

    // Gui lenh list

    // Gui lenh port
    sprintf(sendcmd, "PORT 127,0,0,1,10,1\r\n");
    send(client_sock, sendcmd, strlen(sendcmd), 0);

    ret = recv(client_sock, buf, sizeof(buf), 0);
    buf[ret] = 0;
    printf("%s", buf);

    CreateThread(0, 0, DataThread, 0, 0, 0);

    // gui lenh LIST
    strcpy(sendcmd, "LIST\r\n");
    send(client_sock, sendcmd, strlen(sendcmd), 0);

    ret = recv(client_sock, buf, sizeof(buf), 0);
    buf[ret] = 0;
    printf("%s", buf);

    while (1) 
    {

    }

    closesocket(client_sock);
    WSACleanup();
}