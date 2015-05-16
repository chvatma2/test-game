#include "ship.h"

Ship::Ship(const QVector2D &position, GLuint texture, float speed)
    : MovingObject(position, texture, speed)
{

}

Ship::~Ship()
{

}

