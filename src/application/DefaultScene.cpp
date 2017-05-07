#include "DefaultScene.h"

DefaultScene::DefaultScene(Graphics* graphics) 
:
    Scene(graphics)
{
    ChatWindow* chatWindow = new ChatWindow();
    TitleBar* titleBar = new TitleBar(graphics);
    Client* client = new Client(chatWindow, titleBar);
    Server* server = new Server(chatWindow, titleBar);
    CommandParser* commandParser = new CommandParser(chatWindow, server, client);
    EditBox* editBox = new EditBox(chatWindow, client, commandParser);

    AddObject(chatWindow);
    AddObject(editBox);
    AddObject(client);
    AddObject(server);
    AddObject(titleBar);
}

DefaultScene::~DefaultScene() 
{
}
