#include "Application.h"

Application::Application():
    deltaTime(0.0f),
    graphics(NULL),
    scene(NULL)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        ERROR("Failed to initialize SDL");

    if (TTF_Init() < 0)
        ERROR("Failed to initialize SDL_TTF");

    if (SDLNet_Init() < 0)
        ERROR("Failed to initialize SDL_Net");

    graphics = new Graphics();

    AssetManager::Initialize(graphics);
}

Application::~Application() 
{
    SAFE_DELETE(scene);
    SAFE_DELETE(graphics);

    AssetManager::Deinitialize();

    SDLNet_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Application::Run() 
{
    bool isRunning = true;

    while (isRunning)
    {
        Uint32 frameStart = SDL_GetTicks();

        Input::Reset();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            Input::Update(&event);
        }

        Update(deltaTime);
        Draw();

        deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
    }
}

void Application::SetScene(Scene* scene) 
{
    SAFE_DELETE(this->scene);

    this->scene = scene;
}

void Application::Update(float deltaTime) 
{
    scene->Update(deltaTime);
}

void Application::Draw() 
{
    graphics->Clear();

    scene->Draw(graphics);

    graphics->Present();
}
