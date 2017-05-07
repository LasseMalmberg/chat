#ifndef SERVER_H
#define SERVER_H

#include <cstring>
#include <vector>

#include "SDL.h"
#include "SDL_net.h"

#include "../engine/Object.h"

#include "ChatWindow.h"
#include "TcpConnection.h"
#include "TitleBar.h"

using std::vector;

class Server : public Object
{
public:
    Server(ChatWindow* chatWindow, TitleBar* titleBar);
    ~Server();

    void Update(float deltaTime);
    void Draw(Graphics* graphics) {};

    void Start(Uint16 port);
    void ShutDown();

    bool IsRunning() { return isRunning; }


private:
    void PollForConnections();
    void PollForData();

    vector<TcpConnection*> connections;
    TCPsocket serverSocket;
    Uint16 port;
    bool isRunning;

    ChatWindow* chatWindow;
    TitleBar* titleBar;
};

#endif
