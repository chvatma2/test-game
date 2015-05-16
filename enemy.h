#ifndef ENEMY_H
#define ENEMY_H

#include "ship.h"

class Enemy : public Ship
{
public:
    Enemy(const QVector2D& position, GLuint texture, float speed);
    ~Enemy();
};

#endif // ENEMY_H
