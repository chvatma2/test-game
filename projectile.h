#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector2D>
#include <spritebatch.h>
#include "movingobject.h"

class Projectile : public MovingObject
{
public:
    Projectile(QVector2D& position, QVector2D& direction, QVector2D& size, float speed, int lifeTime, GLuint texture);

    void draw(MyLE::SpriteBatch& spriteBatch);
    void update();
    bool isToBeDestroyed();

private:
    int m_LifeTime;
    bool m_IsToBeDestroyed;
    QVector2D m_Direction;
    QVector2D m_Size;
};

#endif // PROJECTILE_H
