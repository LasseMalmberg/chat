#ifndef EditBox_H
#define EditBox_H

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../engine/Input.h"
#include "../engine/Object.h"
#include "../engine/TextObject.h"

#include "ChatWindow.h"
#include "Client.h"
#include "CommandParser.h"

class EditBox : public Object
{
public:
    EditBox(ChatWindow* chatWindow, Client* client, CommandParser* commandParser);
    ~EditBox();

    void Update(float deltaTime);
    void Draw(Graphics* graphics);

private:
    void AppendMessage(char c);
    void RemoveLastCharacter();
    void ProcessMessage();
    bool AlphabetKeyIsDown(char& c);
    bool NumericKeyIsDown(char& c);
    bool SpecialKeyIsDown(char& c);
    bool MessageIsEmpty(); 
    bool MessageIsFull();
    void UpdateCursor(float deltaTime, bool resetCursor);

    TextObject* message;
    int minMessageLength;
    int maxMessageLength;
    int paddingLeft;
    int paddingTop;

    ChatWindow* chatWindow;
    Client* client;
    CommandParser* commandParser;
};

#endif
