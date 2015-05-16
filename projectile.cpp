#include "projectile.h"

Projectile::Projectile(QVector2D &position, QVector2D &direction, QVector2D &size, float speed, int lifeTime, GLuint texture)
    : MovingObject(position, texture, speed), m_LifeTime(lifeTime), m_IsToBeDestroyed(false), m_Direction(direction), m_Size(size)
{

}

void Projectile::draw(MyLE::SpriteBatch &spriteBatch)
{
    spriteBatch.draw(QVector4D(m_Position, m_Size.x(), m_Size.y()),
                     QVector4D(0.0f, 0.0f, 1.0f, 1.0f),
                     m_Texture,
                     0.0f,
                     QColor(255, 0, 0));
}

void Projectile::update()
{
    m_Position += m_Direction * m_Speed;
    m_LifeTime--;
    if(!m_LifeTime)
        m_IsToBeDestroyed = true;
}

bool Projectile::isToBeDestroyed()
{
    return m_IsToBeDestroyed;
}

