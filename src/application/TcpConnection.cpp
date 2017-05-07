#include "TcpConnection.h"

TcpConnection::TcpConnection(ChatWindow* chatWindow)
:
    chatWindow(chatWindow),
    isConnected(false)
{
    socketSet = SDLNet_AllocSocketSet(1);    
}

TcpConnection::~TcpConnection() 
{
    SDLNet_TCP_DelSocket(socketSet, socket);
    SDLNet_TCP_Close(socket);
    SDLNet_FreeSocketSet(socketSet);    
}

bool TcpConnection::Open(TCPsocket& server) 
{
    socket = SDLNet_TCP_Accept(server);

    if (!socket)
        return false;

    SDLNet_TCP_AddSocket(socketSet, socket);
    isConnected = true;

    IPaddress* ip = SDLNet_TCP_GetPeerAddress(socket);

    // Get client port.
    this->port = std::to_string(ip->port);

    // Get client IP address.
    Uint32 ipaddr = SDL_SwapBE32(ip->host);
    char ipAddress[128];
    snprintf(ipAddress, sizeof(ipAddress), "%d.%d.%d.%d", 
            ipaddr>>24,
            (ipaddr>>16)&0xff, 
            (ipaddr>>8)&0xff,
            ipaddr&0xff);

    this->ipAddress = ipAddress;

    delete ip;

    return true;
}

bool TcpConnection::BytesToRead() 
{
    if (!isConnected)
        return false;

    if (SDLNet_CheckSockets(socketSet, 0))
    {
        return SDLNet_SocketReady(socket);
    }

    return false;
}
