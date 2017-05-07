#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <map>
#include <regex>
#include <string>
#include <vector>

#include "Client.h"
#include "ChatWindow.h"
#include "Command.h"
#include "Server.h"

using namespace std;

class CommandParser
{
public:
    CommandParser(ChatWindow* chatWindow, Server* server, Client* client);
    ~CommandParser();

    int IsCommand(string text);
    void RunCommand(string text);

private:
    vector<string> ExtractCommandPieces(string text);
    void ParseConnectCommand(vector<string> arguments);
    void ParseHelpCommand(vector<string> arguments);
    void ParseHostCommand(vector<string> arguments);

    map<string, Command> commands;

    ChatWindow* chatWindow;
    Server* server;
    Client* client;

};

#endif
