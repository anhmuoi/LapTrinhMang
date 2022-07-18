#include <stdio.h>
#include <winsock2.h>
#include <map>
#include <string>
#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

std::map<std::string, std::string> param_map;

void ProcessQuery(char* req)
{
    char* p1 = strstr(req, " ");
    char* p2 = strstr(p1+1, " ");

    char* query_string = p1 + 1;
    *p2 = 0;

    char* question_mark = strstr(query_string, "?");

    if (question_mark == NULL) return;

    char* param = strtok(question_mark + 1, "&");
    while (param != NULL)
    {
        char* p = strstr(param, "=");
        
        // Tach phan name
        int nameLength = p - param;
        char* name = (char*)malloc(nameLength + 1);
        memcpy(name, param, nameLength);
        name[nameLength] = 0;

        // Tach phan value
        int valueLength = strlen(param) - nameLength - 1;
        char* value = (char*)malloc(valueLength + 1);
        memcpy(value, param + nameLength + 1, valueLength);
        value[valueLength] = 0;

        param_map[name] = value;

        param = strtok(NULL, "&");
    }
}
int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9000);
    bind(listener, (SOCKADDR*)&addr, sizeof(addr));
    listen(listener, 5);
    char buf[2048];
    int ret;
    while (1)
    {
        // Chap nhan ket noi
        SOCKET client = accept(listener, NULL, NULL);
        // Nhan yeu cau
        ret = recv(client, buf, sizeof(buf), 0);
        if (ret <= 0)
        {
            closesocket(client);
            continue;
        }
        // Xu ly yeu cau
        if (ret < sizeof(buf))
            buf[ret] = 0;
        printf("%s\n", buf);
        ProcessQuery(buf);
        
        
        
        if (param_map["param1"] != "" && param_map["param2"] != "") {
            std::string res;
            int sum = 0;

            if (param_map["op"] == "add") {
                sum = stoi(param_map["param1"]) + stoi(param_map["param2"]);
                res = param_map["param1"] +  " + " + param_map["param2"] + " = ";
            }
                
            else if (param_map["op"] == "sub") {
                sum = stoi(param_map["param1"]) - stoi(param_map["param2"]);
                res = param_map["param1"] + " - " + param_map["param2"] + " = ";
            }
            else if (param_map["op"] == "mul") {
                sum = stoi(param_map["param1"]) * stoi(param_map["param2"]);
                res = param_map["param1"] + " * " + param_map["param2"] + " = ";
            }
            else if (param_map["op"] == "div") {
                sum = stoi(param_map["param1"]) / stoi(param_map["param2"]);
                res = param_map["param1"] + " / " + param_map["param2"] + " = ";
            }
            else {
                continue;
            }

            res += std::to_string(sum);

            const char* response = res.c_str();

            const char* header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
            send(client, header, strlen(header), 0);
            send(client, response, strlen(response), 0);
        }
        

        param_map.clear();
        // Tra lai ket qua
        // Dong ket noi
        closesocket(client);
    }
}