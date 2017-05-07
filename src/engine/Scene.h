#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Object.h"
#include "Graphics.h"

using std::vector;

class Scene
{
public:
    virtual ~Scene() = 0;

    void Update(float deltaTime);
    void Draw(Graphics* graphics);

protected:
    Scene(Graphics* graphics);

    void AddObject(Object* object);

    Graphics* graphics;

private:
    vector<Object*> objects;

};

#endif
