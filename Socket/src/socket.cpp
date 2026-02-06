#include "socket.h"

#define TCP_MAXRT 5

Socket::Socket()
{
}

Socket::~Socket()
{
    SocketStop();
    WSACleanup();
}

bool Socket::ConnectToServer()
{
    if (connect(m_connectSocket, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr)) == SOCKET_ERROR)
    {
        return false;
    }
    return true;
}

bool Socket::SocketStart()
{
    m_starting = true;
    SendCall();
    return RecvCall();
}

void Socket::SocketStop()
{
    m_starting = false;
    if (m_connectSocket != INVALID_SOCKET)
    {
        shutdown(m_connectSocket, SD_BOTH);
        closesocket(m_connectSocket);
        m_connectSocket = INVALID_SOCKET;
    }
}

void Socket::Settings(std::string ip, size_t port)
{
    m_serverIp = ip;
    m_server_Port = port;
    WSAStartup(MAKEWORD(2, 2), &m_wsaData);
    m_connectSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    DWORD toMs = 3000; // 3.0 second
    DWORD maxRt = 5; // 5 retransmissions
    setsockopt(m_connectSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&toMs, sizeof(toMs)); // Receive timeout
    setsockopt(m_connectSocket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&toMs, sizeof(toMs)); // Send timeout
    setsockopt(m_connectSocket, IPPROTO_TCP, TCP_MAXRT, (const char*)&maxRt, sizeof(maxRt)); // Max retransmissions

    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(static_cast<u_short>(m_server_Port));
    m_serverAddr.sin_addr.s_addr = inet_addr(m_serverIp.c_str());
    if(!ConnectToServer())
    {
        std::cerr << "Unable to connect to server!" << std::endl;
    };
}

bool Socket::RecvCall()
{
    char buffer[64] = {};
    int iserror = recv(m_connectSocket, buffer, sizeof(buffer), 0);
    if(iserror == 0) //안정적 연결 종료
    {
        return false;
    }
    if(iserror < 0) //오류 발생
    {
        return false;
    }
    m_acc.append(buffer, iserror);
    size_t pos = 0u;
    while((pos = m_acc.find('\n'))!= std::string::npos) //npos 못찾음 특수 값
    {
        std::string line = m_acc.substr(0, pos); //m_acc 에서 한줄 자름
        m_acc.erase(0, pos + 1); //자른만큼 acc에서 제거

        bool netwhitespace = false;
        for(unsigned char c : line)
        {
            if(!std::isspace(c)) { //공백 체크
                netwhitespace = true;
                break;
            }
        }
        if (!netwhitespace) {continue;}
        try { //문자열을 double로 변환
            m_data = std::stod(line);
            switch(m_flag) {
                case '0':
                    std::cout << "CPU Data from server: " << m_data << std::endl;
                    break;
                case '1':
                    std::cout << "Memory Data from server: " << m_data << std::endl;
                    break;
                case '2':
                    std::cout << "Disk Data from server: " << m_data << std::endl;
                    break;
                default:
                    break;
            }
        } catch (...) {
            std::cout << "bad line: [" << line << "]\n";
        }

    }
    return true;
}

bool Socket::SendCall()
{
    int is_error = send(m_connectSocket,(char*)&m_flag, sizeof(char),0);
    if(is_error <= 0 )
    {
        return false;
    }

    return true;
}