#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

#include "../engine/Scene.h"
#include "../engine/TextObject.h"

#include "ChatWindow.h"
#include "Client.h"
#include "CommandParser.h"
#include "EditBox.h"
#include "Server.h"
#include "TitleBar.h"

class DefaultScene : public Scene
{
public:
    DefaultScene(Graphics* graphics);
    ~DefaultScene();
};

#endif
