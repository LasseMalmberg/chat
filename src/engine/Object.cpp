#include "Object.h"

Object::Object(): 
    transform(new Transform())
{
}

Object::~Object() 
{
    SAFE_DELETE(transform);
}
