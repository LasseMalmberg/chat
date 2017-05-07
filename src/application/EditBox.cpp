#include "EditBox.h"

EditBox::EditBox(ChatWindow* chatWindow, Client* client, CommandParser* commandParser):
    message(new TextObject("|")),
    minMessageLength(2),
    maxMessageLength(67),
    paddingLeft(10),
    paddingTop(10),
    chatWindow(chatWindow),
    client(client),
    commandParser(commandParser)
{
    SetPosition(20, 650);
    message->SetPosition(GetPosition().x + paddingLeft, GetPosition().y + paddingTop);
}

EditBox::~EditBox() 
{
    SAFE_DELETE(message);
}

void EditBox::Update(float deltaTime) 
{
    // Only one key can be down per frame due to how input is checked (exluding shift). 
    // If a pressed key is recognized, the checks for the rest of the keys are skipped.

    if (Input::IsKeyDown(SDLK_BACKSPACE))
    {
        RemoveLastCharacter();
        UpdateCursor(deltaTime, true);
        return;
    }

    if (Input::IsKeyDown(SDLK_RETURN) && !MessageIsEmpty())
    {
        ProcessMessage();
        return;
    }

    if (MessageIsFull())
    {
        return;
    }

    char c = '\0';

    if (AlphabetKeyIsDown(c) ||
        NumericKeyIsDown(c) ||
        SpecialKeyIsDown(c))
    {
        AppendMessage(c);
        return;
    }

    UpdateCursor(deltaTime, false);
}

void EditBox::Draw(Graphics* graphics) 
{
    SDL_SetRenderDrawColor(graphics->GetRenderer(), 247, 247, 247, 255);
    SDL_Rect rect = { GetPosition().x, GetPosition().y, 1240, 50 };
    SDL_RenderDrawRect(graphics->GetRenderer(), &rect);

    message->Draw(graphics);
}

void EditBox::AppendMessage(char c) 
{
    static std::stringstream ss;

    string msg = message->GetText();
    msg.erase(msg.length() - 1, 1);

    ss << msg << c << "|";

    message->SetText(ss.str());

    ss.str("");
    ss.clear();
}

void EditBox::RemoveLastCharacter() 
{
    string text = message->GetText();

    if (text.size() <= 1)
    {
        // An empty string can't be rendered. 
        // The message is set to a space to fix this.
        text = " ";
    }
    else
    {
        // Remove last character.
        text = text.substr(0, text.size() - 1);
    }

    message->SetText(text);
}

void EditBox::ProcessMessage() 
{
    // Remove cursor.
    RemoveLastCharacter();

    string text = message->GetText();

    // Remove leading space.
    /* text.erase(0, 1); */ 
    

    int result = commandParser->IsCommand(text);

    if (result == -1) // Text is an invalid command.
    {
        string error = "Invalid command: \"" + text + "\".";
        chatWindow->AddMessage(error);
    }
    else if (result == 0) // Text is not a command; it is a message.
    {
        chatWindow->AddMessage(text);
        client->SendMessage(text);
    }
    else if (result == 1) // Text is a valid command.
    {
        commandParser->RunCommand(text);
    }

    // Reset the message in the edit box.
    string s = " ";
    message->SetText(s);
}

bool EditBox::AlphabetKeyIsDown(char& c) 
{
    static char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 26; i++)
    {
        if (Input::IsKeyDown(alphabet[i]))
        {
            c = alphabet[i];

            if (Input::IsShiftDown())
            {
                c = toupper(c);
            }

            return true;
        }
    }

    return false;
}

bool EditBox::NumericKeyIsDown(char& c) 
{
    // Shift is down; can't be a number.
    if (Input::IsShiftDown())
        return false;

    static char numbers[] = "0123456789";

    for (int i = 0; i < 10; i++)
    {
        if (Input::IsKeyDown(numbers[i]))
        {
            c = numbers[i];

            return true;
        }
    }

    return false;
}

bool EditBox::SpecialKeyIsDown(char& c) 
{
    c = '\0';

    if (Input::IsKeyDown(SDLK_SPACE))
        c = ' ';
    else if (Input::IsKeyDown(SDLK_PERIOD))
        c = '.';
    else if (Input::IsKeyDown(SDLK_COMMA))
        c = ',';
    else if (Input::IsKeyDown(SDLK_QUOTE))
        c = '\'';
    else if (Input::IsShiftDown() && Input::IsKeyDown(SDLK_1))
        c = '!';
    else if (Input::IsShiftDown() && Input::IsKeyDown(SDLK_7))
        c = '/';
    else if (Input::IsShiftDown() && Input::IsKeyDown(SDLK_PLUS))
        c = '?';

    return (c == '\0') ? false : true;
}

bool EditBox::MessageIsEmpty() 
{
    return message->GetTextLength() < minMessageLength;
}

bool EditBox::MessageIsFull() 
{
    return message->GetTextLength() > maxMessageLength;
}

void EditBox::UpdateCursor(float deltaTime, bool resetCursor)
{
    static float timeElapsed = 0;

    timeElapsed += deltaTime;

    if (timeElapsed < 0.75f && !resetCursor)
        return;

    string msg = message->GetText();

    if (msg[msg.length() - 1] == '|')
        msg[msg.length() - 1] = ' ';
    else
        msg[msg.length() - 1] = '|';

    timeElapsed = 0.0f;
    message->SetText(msg);
}
