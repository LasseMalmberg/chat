#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "SDL.h"
#include "SDL_net.h"
#include "SDL_ttf.h"

#include "AssetManager.h"
#include "Global.h"
#include "Graphics.h"
#include "Input.h"
#include "Scene.h"

using std::vector;

class Application
{
public:
    Application();
    virtual ~Application() = 0;

    void Run();

protected:
    void SetScene(Scene* scene);

    Graphics* graphics;

private:
    void Update(float deltaTime);
    void Draw();

    float deltaTime;

    Scene* scene;


};

#endif
