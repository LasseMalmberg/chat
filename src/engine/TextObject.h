#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "SDL_ttf.h"

#include "AssetManager.h"
#include "Object.h"


class TextObject : public Object
{
public:
    TextObject(string text);
    ~TextObject();

    void Update(float deltaTime);
    void Draw(Graphics* graphics);

    string GetText() const { return text; }
    int GetTextLength() { return text.length(); }

    void SetText(string text);

private:
    string text;
    int textureWidth;
    int textureHeight;

    SDL_Texture* texture;
};

#endif
