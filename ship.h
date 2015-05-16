#ifndef SHIP_H
#define SHIP_H

#include "movingobject.h"

class Ship : public MovingObject
{
public:
    Ship(const QVector2D& position, GLuint texture, float speed);
    virtual ~Ship();

};

#endif // SHIP_H
