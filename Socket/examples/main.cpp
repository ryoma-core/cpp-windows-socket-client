#include "socket.h"

int main()
{
    Socket clientSocket;
    clientSocket.ChangeFlag('0');
    clientSocket.Settings("192.168.0.100", 1869);
    clientSocket.SocketStart();
}