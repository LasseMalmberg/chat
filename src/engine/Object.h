#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "Global.h"
#include "Graphics.h"
#include "Transform.h"

using std::string;

class Object
{
public:
    virtual ~Object();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(Graphics* graphics) = 0;

    Vector2 GetPosition() const { return transform->position; }
    Vector2 GetScale() const { return transform->scale; }

    void SetPosition(float x, float y) { transform->position = Vector2(x, y); }
    void SetPosition(Vector2 position) { transform->position = position; }
    void SetScale(float x, float y) { transform->scale = Vector2(x, y); }
    void SetScale(Vector2 scale) { transform->scale = scale; }

protected:
    Object();

private:
    Transform* transform;
};

#endif
