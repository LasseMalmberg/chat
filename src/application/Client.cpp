#include "Client.h"

Client::Client(ChatWindow* chatWindow, TitleBar* titleBar)
:
    username(""),
    isConnected(false),
    chatWindow(chatWindow),
    titleBar(titleBar)
{
    socketSet = SDLNet_AllocSocketSet(1);
}

Client::~Client() 
{
    Disconnect(false, true);
    SDLNet_FreeSocketSet(socketSet);
}

void Client::Update(float deltaTime)
{
    if (IsConnected())
    {
        PollForData();
    }
}

void Client::Draw(Graphics* graphics) 
{
}

void Client::SendMessage(string message) 
{
    if (isConnected)
    {
        message = "[" + username + "] " + message;
        int length = message.length();
        SDLNet_TCP_Send(socket, message.c_str(), length);
    }
}

void Client::PollForData()
{
    if (!isConnected)
        return;

    if (SDLNet_CheckSockets(socketSet, 0))
    {
        if (SDLNet_SocketReady(socket))
        {
            const int bufferSize = 511;
            char buffer[bufferSize + 1];

            int bytes = SDLNet_TCP_Recv(socket, buffer, bufferSize);

            switch (bytes)
            {
                // An error occurred or the server closed the connection.
                case -1:
                case 0: 
                    Disconnect();
                    break;

                default:
                    buffer[bytes] = '\0';

                    // Server explicitly shut down.
                    if (std::strcmp(buffer, "SERVER_SHUTDOWN_DISCONNECT") == 0)
                    {
                        Disconnect(true);
                    }
                    else
                    {
                        chatWindow->AddMessage(buffer);
                    }

                    break;
            }
        }
    }
}

void Client::Connect(string ipAddress, int port, string username)
{
    if (isConnected)
        return;

    this->username = username;

    SDLNet_ResolveHost(&serverIpAddress, ipAddress.c_str(), port);
    socket = SDLNet_TCP_Open(&serverIpAddress);

    if (!socket)
    {
        chatWindow->AddMessage("# Failed to connect to server");
        return;
    }

    isConnected = true;
    SDLNet_TCP_AddSocket(socketSet, socket);

    chatWindow->AddMessage("# Connected to server");
    string message = "# [" + username + "] connected";
    Broadcast(message);

    titleBar->SetIsConnected(true);
    titleBar->SetUsername(username);
    titleBar->SetServerIpAddress(ipAddress);
    titleBar->SetServerPort(port);
}

void Client::Disconnect(bool serverShutDown, bool programClosed)
{
    if (!isConnected)
        return;

    // Disconnection was not caused by closing the program; add a local chat message.
    if (!programClosed)
    {
        chatWindow->AddMessage("# Disconnected from server");
        titleBar->SetIsConnected(false);
    }

    // Disconnection was not caused by the server shutting down; broadcast a message.
    if (!serverShutDown)
    {
        string message = "# [" + username + "] disconnected";
        Broadcast(message);
    }

    SDLNet_TCP_DelSocket(socketSet, socket);
    SDLNet_TCP_Close(socket);
    isConnected = false;
}

// Broadcasts a message to other clients without the user's username.
void Client::Broadcast(string message)
{
    int length = message.length();
    SDLNet_TCP_Send(socket, message.c_str(), length);
}
