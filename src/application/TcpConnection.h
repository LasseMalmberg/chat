#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <cstdio>

#include "SDL_net.h"

#include "../engine/Global.h"

#include "ChatWindow.h"

class TcpConnection
{
public:
    TcpConnection(ChatWindow* chatWindow);
    ~TcpConnection();

    bool Open(TCPsocket& server);

    TCPsocket Socket() { return socket; }
    SDLNet_SocketSet SocketSet() { return socketSet; }
    bool IsConnected() { return isConnected; }
    bool BytesToRead();

    string GetIpAddress() { return ipAddress; }
    string GetPort() { return port; }

private:
    TCPsocket socket;
    SDLNet_SocketSet socketSet;
    string ipAddress;
    string port;
    bool isConnected;

    ChatWindow* chatWindow;
};

#endif
