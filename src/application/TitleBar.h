#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include <sstream>
#include <string>

#include "../engine/Graphics.h"
#include "../engine/Object.h"

using std::string;

class TitleBar : public Object
{
public:
    TitleBar(Graphics* graphics);
    ~TitleBar();

    void Update(float deltaTime);
    void Draw(Graphics* graphics);

    void SetIsConnected(bool state);
    void SetIsHosting(bool state);
    void SetUsername(string username);
    void SetServerIpAddress(string ipAddress);
    void SetServerPort(int port);
    void SetHostedPort(int port);

private:
    void UpdateTitleBar();

    bool isConnected;
    bool isHosting;

    string applicationName;
    string username;
    string serverIpAddress;
    string serverPort;
    string hostedPort;
    string msgDelimiter;

    Graphics* graphics;
};

#endif
