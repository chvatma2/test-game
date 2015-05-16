#ifndef PLAYER_H
#define PLAYER_H

#include <inputmanager.h>

#include "ship.h"

class Player : public Ship
{
public:
    Player(const QVector2D &position, GLuint texture, float speed, MyLE::InputManager* inputManager);
    ~Player();

    void update();

private:
    MyLE::InputManager* m_InputManager;
};

#endif // PLAYER_H
