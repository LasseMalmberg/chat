#include "TitleBar.h"

TitleBar::TitleBar(Graphics* graphics) 
:
    isConnected(false),
    isHosting(false),
    applicationName("Chat"),
    username(""),
    serverIpAddress(""),
    serverPort(""),
    hostedPort(""),
    msgDelimiter("    |    "),
    graphics(graphics)
{
    UpdateTitleBar();
}

TitleBar::~TitleBar() 
{
}

void TitleBar::Update(float deltaTime) 
{
}

void TitleBar::Draw(Graphics* graphics)
{
}

void TitleBar::UpdateTitleBar() 
{
    std::stringstream ss;

    ss << applicationName << msgDelimiter;

    // Connection status.
    if (isConnected)
        ss << "Connected [ " << serverIpAddress << " : " << serverPort << " ]";
    else
        ss << "Not connected";

    ss << msgDelimiter;

    if (!username.empty())
        ss << username << msgDelimiter;

    // Hosting status.
    if (isHosting)
        ss << "Hosting [ " << hostedPort << " ]";
    else
        ss << "Not hosting";

    string title = ss.str();

    SDL_SetWindowTitle(graphics->GetWindow(), title.c_str());
}

void TitleBar::SetIsConnected(bool state) 
{
    if (state == false)
        username = "";

    isConnected = state;
    UpdateTitleBar();
}

void TitleBar::SetIsHosting(bool state) 
{
    isHosting = state;
    UpdateTitleBar();
}

void TitleBar::SetUsername(string username) 
{
    this->username = username;
    UpdateTitleBar();
}

void TitleBar::SetServerIpAddress(string ipAddress) 
{
    serverIpAddress = ipAddress;
}

void TitleBar::SetHostedPort(int port) 
{
    hostedPort = std::to_string(port);
    UpdateTitleBar();
}

void TitleBar::SetServerPort(int port) 
{
    serverPort = std::to_string(port);
    UpdateTitleBar();
}
