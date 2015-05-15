#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QVector2D>
#include <spritebatch.h>

class Projectile
{
public:
    Projectile(QVector2D& position, QVector2D& direction, QVector2D& size, float speed, int lifeTime);

    void draw(MyLE::SpriteBatch& spriteBatch);
    void update();
    bool isToBeDestroyed();

private:
    float m_Speed;
    int m_LifeTime;
    bool m_IsToBeDestroyed;
    QVector2D m_Position;
    QVector2D m_Direction;
    QVector2D m_Size;
};

#endif // PROJECTILE_H
