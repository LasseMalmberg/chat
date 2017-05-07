#include "Scene.h"

Scene::Scene(Graphics* graphics) 
:
    graphics(graphics)
{
}

Scene::~Scene() 
{
    for (uint i = 0; i < objects.size(); i++)
    {
        SAFE_DELETE(objects[i]);
        objects.erase(objects.begin() + i);
    }
}

void Scene::Update(float deltaTime) 
{
    for (uint i = 0; i < objects.size(); i++)
    {
        objects[i]->Update(deltaTime);
    }
}

void Scene::Draw(Graphics* graphics) 
{
    for (uint i = 0; i < objects.size(); i++)
    {
        objects[i]->Draw(graphics);
    }
}

void Scene::AddObject(Object* object) 
{
    objects.push_back(object); 
}
