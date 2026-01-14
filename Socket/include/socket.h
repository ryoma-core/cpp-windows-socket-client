#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32")


class Socket 
{
    public:
        Socket(std::string ip , size_t port);
        ~Socket();
        void socket_start();
        void socket_stop();
        bool connect_to_server();
    private:
    #pragma region Members
        std::string server_Ip;
        size_t server_Port;
        WSADATA wsaData;
        SOCKET connectSocket;
        SOCKADDR_IN serverAddr = {};
        bool wait = false;
        double data = 0;
        char flag = '0';
        bool finish = false;
        std::string acc;
    #pragma endregion
    #pragma region Methods
    bool recvCall();
    bool sendCall();
    #pragma endregion

};