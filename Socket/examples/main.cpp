#include "socket.h"

int main()
{
    Socket clientSocket("192.168.0.101", 1869);
    clientSocket.socket_start();
}