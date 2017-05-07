#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <vector>

#include "../engine/Object.h"
#include "../engine/TextObject.h"

using std::vector;

class ChatWindow : public Object
{
public:
    ChatWindow();
    ~ChatWindow();

    void Update(float deltaTime);
    void Draw(Graphics* graphics);

    void AddMessage(string msg);
    void AddHelpMessage();
    void Clear();

private:
    vector<TextObject*> messages;

    int maxMessages;
    int width;
    int height;
    int paddingLeft;
    int paddingBottom;
    int messageMargin;
};

#endif
