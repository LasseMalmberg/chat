#include "Server.h"

Server::Server(ChatWindow* chatWindow, TitleBar* titleBar)
:
    isRunning(false),
    chatWindow(chatWindow),
    titleBar(titleBar)
{
    // Add an empty connection that clients can connect to.
    connections.push_back(new TcpConnection(chatWindow));
}

Server::~Server() 
{
    ShutDown();
}

void Server::Update(float deltaTime) 
{
    if (isRunning)
    {
        PollForConnections();
        PollForData();
    }
}

void Server::PollForConnections() 
{
    // Opens a connection if any are pending on serverSocket.
    connections.back()->Open(serverSocket);

    // A new connection was opened.
    if (connections.back()->IsConnected())
    {
        string s = "# " + connections.back()->GetIpAddress() + ":" + 
            connections.back()->GetPort() + " connected";

        chatWindow->AddMessage(s);
        
        // Add an empty connection that clients can connect to.
        connections.push_back(new TcpConnection(chatWindow));
    }
}

void Server::PollForData() 
{
    // Check client connections for incoming data.
    for (int i = 0; i < connections.size(); i++)
    {
        if (connections[i]->BytesToRead())
        {
            // Read the incoming data into a buffer.
            const int bufferSize = 511;
            char buffer[bufferSize + 1];
            int bytes = SDLNet_TCP_Recv(connections[i]->Socket(), buffer, bufferSize);

            switch (bytes)
            {
                // An error occurred or the socket was closed by the client.
                // The connection is removed.
                case -1:
                case 0:
                {
                    string s = "# " + connections[i]->GetIpAddress() + ":" + 
                        connections[i]->GetPort() + " disconnected";

                    chatWindow->AddMessage(s);

                    delete connections[i];
                    connections.erase(connections.begin() + i);
                    break;
                }

                // Data has been received. 
                // The data is forwarded to other connected clients, excluding the sending client.
                default:
                    buffer[bytes] = '\0';

                    for (int k = 0; k < connections.size(); k++)
                    {
                        if (k != i && connections[k]->IsConnected())
                        {
                            SDLNet_TCP_Send(connections[k]->Socket(), buffer, bufferSize);
                        }
                    }

                    break;
            }
        }
    }
}

void Server::Start(Uint16 port) 
{
    if (isRunning)
        return;

    // Open a socket for incoming connections.
    IPaddress ipAddress;
    SDLNet_ResolveHost(&ipAddress, NULL, port);
    serverSocket = SDLNet_TCP_Open(&ipAddress);

    this->port = port;
    isRunning = true;

    chatWindow->AddMessage("# Hosting a server");

    titleBar->SetIsHosting(true);
    titleBar->SetHostedPort(port);
}

void Server::ShutDown() 
{
    if (!isRunning)
        return;

    // Instruct clients to disconnect.
    string message = "SERVER_SHUTDOWN_DISCONNECT";
    for (int i = 0; i < connections.size() - 1; i++)
    {
        int length = message.length();
        SDLNet_TCP_Send(connections[i]->Socket(), message.c_str(), length);
    }

    // Remove all connections.
    for (int i = 0; i < connections.size(); i++)
    {
        delete connections[i];
        connections.erase(connections.begin() + i);
    }
    
    connections.clear();
    
    // Add an empty connection in case the server is restarted.
    connections.push_back(new TcpConnection(chatWindow));

    SDLNet_TCP_Close(serverSocket);
    isRunning = false;

    chatWindow->AddMessage("# Shut down server");

    titleBar->SetIsHosting(false);
}
