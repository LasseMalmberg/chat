#include "ChatWindow.h"

ChatWindow::ChatWindow():
    maxMessages(17),
    width(1240),
    height(615),
    paddingLeft(15),
    paddingBottom(22),
    messageMargin(35)
{
    SetPosition(20, 20);
    AddMessage("# Simple Client-Server Chat");
    AddHelpMessage();
}

ChatWindow::~ChatWindow() 
{
    for (int i = 0; i < messages.size(); i++)
    {
        SAFE_DELETE(messages[i]);
    }
}

void ChatWindow::Update(float deltaTime) 
{
}

void ChatWindow::Draw(Graphics* graphics) 
{
    // Draw the chat window's edges.
    SDL_SetRenderDrawColor(graphics->GetRenderer(), 247, 247, 247, 255);
    SDL_Rect rect = { GetPosition().x, GetPosition().y, width, height};
    SDL_RenderDrawRect(graphics->GetRenderer(), &rect);

    // Draw the messages.
    for (int i = 0; i < messages.size(); i++)
    {
        messages[i]->Draw(graphics);
    }
}

void ChatWindow::AddMessage(string msg) 
{
    // If the chat window is full, remove the oldest message.
    if (messages.size() >= maxMessages)
    {
        delete messages[messages.size() - 1];
        messages.pop_back();
    }

    // Reposition existing messages.
    for (int i = 0; i < messages.size(); i++)
    {
        Vector2 p = messages[i]->GetPosition();
        messages[i]->SetPosition(p.x, p.y - messageMargin);
    }

    // Add the new message.
    TextObject* message = new TextObject(msg);
    message->SetPosition(GetPosition().x + paddingLeft, height - paddingBottom);
    messages.insert(messages.begin(), message);
}

void ChatWindow::Clear() 
{
    for (int i = 0; i < messages.size(); i++)
    {
        delete messages[i]; 
    }

    messages.clear();
}

void ChatWindow::AddHelpMessage() 
{
    vector<string> messages;

    messages.push_back("# Commands: clear, connect, disconnect, help, host, quit, shutdown");
    messages.push_back("# Type \"/help [command]\" to view help for a specific command");
    messages.push_back("# Commands are of the format \"/[command] [argument1] ... [argumentN]\"");

    for (int i = 0; i < messages.size(); i++)
    {
        AddMessage(messages[i]);
    }    
}
