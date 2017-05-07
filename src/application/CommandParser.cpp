#include "CommandParser.h"

CommandParser::CommandParser(ChatWindow* chatWindow, Server* server, Client* client)
:
    chatWindow(chatWindow),
    server(server),
    client(client)
{
    // Set the valid commands.
    commands["clear"] = CLEAR;
    commands["cls"] = CLEAR;
    commands["connect"] = CONNECT;
    commands["c"] = CONNECT;
    commands["disconnect"] = DISCONNECT;
    commands["dc"] = DISCONNECT;
    commands["help"] = HELP;
    commands["h"] = HELP;
    commands["host"] = HOST;
    commands["quit"] = QUIT;
    commands["q"] = QUIT;
    commands["shutdown"] = SHUTDOWN;
    commands["sd"] = SHUTDOWN;
}

// Parses text to determine if it is a command.
// A command is of the format "/command argument1 argument2 .. argumentN".
// Returns -1 (invalid command), 0 (not a command i.e. no forward slash), or 1 (valid command).
int CommandParser::IsCommand(string text) 
{
    // A command starts with a forward slash.
    if (text[0] != '/')
        return 0;

    // Append text with a space in case the command has no arguments.
    text += " ";

    // Find the position that comes after the command but before any arguments.
    size_t position = text.find(" ");

    // Extract the command. Account for the leading forward slash.
    string command = text.substr(1, position - 1);

    // Search the list of commands for the extracted command.
    if (commands.count(command))
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void CommandParser::RunCommand(string text) 
{
    // Split text into pieces (the command and its arguments).
    vector<string> arguments = ExtractCommandPieces(text);
    string command = arguments[0];

    switch (commands[command])
    {
        case CLEAR:
            chatWindow->Clear();
            break;

        case CONNECT:
            ParseConnectCommand(arguments);
            break;

        case DISCONNECT:
            client->Disconnect();
            break;

        case HELP:
            ParseHelpCommand(arguments);
            break;

        case HOST:
            ParseHostCommand(arguments);
            break;
            
        case QUIT:
        {
            client->Disconnect();
            server->ShutDown();

            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);

            break;
        }

        case SHUTDOWN:
            server->ShutDown();
            break;
    }
}

vector<string> CommandParser::ExtractCommandPieces(string text) 
{
    // Remove leading forward slash.
    text.erase(0, 1);

    // Append text with a space in case the command has no arguments.
    text += " ";

    vector<string> arguments;
    string delimiter = " ";
    size_t position = 0;

    while ((position = text.find(delimiter)) != string::npos)
    {
        string piece = text.substr(0, position);
        arguments.push_back(piece);
        text.erase(0, position + delimiter.length());
    }

    return arguments;
}

void CommandParser::ParseConnectCommand(vector<string> arguments) 
{
    // Validate argument count (including the command itself).
    if (arguments.size() != 4)
    {
        chatWindow->AddMessage("# Invalid number of arguments to command \"/connect\"");
        return;
    }

    string ip = arguments[1];
    string portAsString = arguments[2];
    string username = arguments[3];
    string errorMessage = "";

    // Validate IP address with a regular expression.
    string r = "\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";
    regex ipRegex(r);

    if (!regex_search(ip, ipRegex) && ip != "localhost")
    {
        errorMessage = "# Invalid IP address";
    }

    // Validate port number.
    int port;
    if ((sscanf(portAsString.c_str(), "%d", &port) == EOF) || // Port is not a number.
        (port < 1 || port > 65525)) // Port is out of range.
    {
        errorMessage = "# Invalid port number";
    }

    // Validate username.
    if (username.length() < 2 || username.length() > 15)
    {
        errorMessage = "# Invalid username. A username must be 2 to 15 characters long";
    }

    // Error occurred (invalid arguments).
    if (errorMessage.length() != 0)
    {
        chatWindow->AddMessage(errorMessage);
        return;
    }

    client->Connect(ip, port, username);
}

void CommandParser::ParseHelpCommand(vector<string> arguments) 
{
    // No arguments, post generic help message.
    if (arguments.size() == 1)
    {
        chatWindow->AddHelpMessage();
        return;
    }

    // Validate argument count (including the command itself).
    if (arguments.size() != 2)
    {
        chatWindow->AddMessage("# Invalid number of arguments to command \"/help\"");
        return;
    }

    // Confirm that the command that help is sought for is a command.
    string command = "/" + arguments[1];
    if (IsCommand(command) == -1)
    {
        chatWindow->AddMessage("# Can't find help information for \"" + command + "\""); 
        return;
    }

    // Display help for argument command.
    vector<string> helpMessages;

    switch (commands[arguments[1]])
    {
        case CLEAR:
            helpMessages.push_back("# Command \"/clear\" clears the chat window");
            helpMessages.push_back("# Alternative form: \"/cls\"");
            break;

        case CONNECT:
            helpMessages.push_back("# Command \"/connect\" connects to a server");
            helpMessages.push_back("# Format: \"/connect [ip] [port] [username]\"");
            helpMessages.push_back("# Example: \"/connect 192.168.0.12 50000 Lasse\"");
            helpMessages.push_back("# Abbreviation: \"/c\". Addresses 127.0.0.1 and localhost are interchangeable");
            break;

        case DISCONNECT:
            helpMessages.push_back("# Command \"/disconnect\" disconnects the client from the server");
            helpMessages.push_back("# Abbreviation: \"/dc\"");
            break;

        case HELP:
            helpMessages.push_back("# Command \"/help\" provides help information for commands");
            helpMessages.push_back("# Format: \"/help [command]\"");
            helpMessages.push_back("# Example: \"/help connect\"");
            helpMessages.push_back("# Abbreviation: \"/h\"");
            break;

        case HOST:
            helpMessages.push_back("# Command \"/host\" starts hosting a server at [port]");
            helpMessages.push_back("# Format: \"/host [port]\"");
            helpMessages.push_back("# Example: \"/host 50000\"");
            break;
            
        case QUIT:
            helpMessages.push_back("# Command \"/quit\" closes the program");
            helpMessages.push_back("# Abbreviation: \"/q\"");
            break;

        case SHUTDOWN:
            helpMessages.push_back("# Command \"/shutdown\" shuts down the server");
            helpMessages.push_back("# Abbreviation: \"/sd\"");
            break;
    }

    for (int i = 0; i < helpMessages.size(); i++)
    {
        if (!helpMessages[i].empty())
            chatWindow->AddMessage(helpMessages[i]);
    }
}

void CommandParser::ParseHostCommand(vector<string> arguments) 
{
    // Validate argument count (including the command itself).
    if (arguments.size() != 2)
    {
        chatWindow->AddMessage("# Invalid number of arguments to command \"/host\"");
        return;
    }

    string portAsString = arguments[1];

    // Validate port number.
    int port;
    if ((sscanf(portAsString.c_str(), "%d", &port) == EOF) || // Port is not a number.
        (port < 1 || port > 65525)) // Port is out of range.
    {
        chatWindow->AddMessage("# Invalid port number");
        return;
    }

    server->Start(port);
}
