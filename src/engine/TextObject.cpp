#include "TextObject.h"

TextObject::TextObject(string text):
    text(text),
    textureWidth(0),
    textureHeight(0)
{
    texture = AssetManager::ConvertStringToTexture(text, textureWidth, textureHeight);
    SetScale(0.6f, 0.6f);
}

TextObject::~TextObject() 
{
    SDL_DestroyTexture(texture);
}

void TextObject::Update(float deltaTime) 
{
}

void TextObject::Draw(Graphics* graphics) 
{
    SDL_Rect image = { 
        0,
        0,
        textureWidth,
        textureHeight
    };

    SDL_Rect position = {
        GetPosition().x,
        GetPosition().y,
        (int)(GetScale().x * textureWidth),
        (int)(GetScale().y * textureHeight)
    };

    SDL_RenderCopy(graphics->GetRenderer(), texture, &image, &position);
}

void TextObject::SetText(string text) 
{
    this->text = text;

    SDL_DestroyTexture(texture);
    texture = AssetManager::ConvertStringToTexture(text, textureWidth, textureHeight);
}
