#include "socket.h"

Socket::Socket(std::string ip , size_t port)
{
    server_Ip = ip;
    server_Port = port;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    connectSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(static_cast<u_short>(server_Port));
    serverAddr.sin_addr.s_addr = inet_addr(server_Ip.c_str());
    connect_to_server();
}

Socket::~Socket()
{
    socket_stop();
}

bool Socket::connect_to_server()
{
    if (connect(connectSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

void Socket::socket_start()
{
 while(!finish)
 {
    std::cin >> flag;
    if(sendCall())
    {
        if(recvCall())
        {
            continue;
        }
    }
    else {
        break;
    }
 }
}

void Socket::socket_stop()
{
    closesocket(connectSocket);
    WSACleanup();
}

bool Socket::recvCall()
{
    char buffer[64] = {};
    int is_error = recv(connectSocket, buffer, sizeof(buffer), 0);
    if( is_error <= 0 )
    {
        finish = true;
        return false;
    }
    acc.append(buffer, is_error);
    size_t pos = 0u;
    while((pos = acc.find('\n'))!= std::string::npos) //npos 못찾음 특수 값
    {
        std::string line = acc.substr(0, pos); //acc 에서 한줄 자름
        acc.erase(0, pos + 1); //자른만큼 acc에서 제거

        bool all_ws = true;
        for(unsigned char c : line)
        {
            if(!std::isspace(c)) {
                all_ws = false;
                break;
            }
        }
        if (all_ws) {continue;}
        try {
            data = std::stod(line);
            std::cout << "Data from server: " << data << std::endl;
        } catch (...) {
            std::cout << "bad line: [" << line << "]\n";
        }

    }
    return true;
}

bool Socket::sendCall()
{
    int is_error = send(connectSocket,(char*)&flag, sizeof(char),0);
    if(is_error <= 0 )
    {
        finish = true;
        return false;
    }

    return true;
}