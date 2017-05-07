#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <cstring>
#include <string>

#include "SDL_net.h"

#include "../engine/Object.h"

#include "ChatWindow.h"
#include "TitleBar.h"

using std::string;

class Client : public Object
{
public:
    Client(ChatWindow* chatWindow, TitleBar* titleBar);
    ~Client();

    void Update(float deltaTime);
    void Draw(Graphics* graphics);

    void Connect(string serverIpAddress, int serverPort, string username);
    void Disconnect(bool serverShutDown = false, bool programClosed = false);

    void SendMessage(string message);
    void Broadcast(string message);
    void PollForData();

    bool IsConnected() { return isConnected; }

private:
    IPaddress serverIpAddress;
    Uint16 serverPort;
    TCPsocket socket;
    SDLNet_SocketSet socketSet;
    string username;
    bool isConnected;

    ChatWindow* chatWindow;
    TitleBar* titleBar;
};

#endif
