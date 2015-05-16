#include "gameobject.h"

GameObject::GameObject(const QVector2D &position, GLuint texture)
    : m_Position(position), m_Texture(texture)
{

}

GameObject::~GameObject()
{

}

void GameObject::draw(MyLE::SpriteBatch &spriteBatch)
{
    QVector4D destination(m_Position.x(), m_Position.y(), OBJECT_SIZE, OBJECT_SIZE);
    const QVector4D uv(0.0f, 0.0f, 1.0f, 1.0f);
    spriteBatch.draw(destination,
                     uv,
                     m_Texture,
                     0.0f,
                     QColor(255,255,255,255));
}

QVector2D GameObject::getPosition() const
{
    return m_Position;
}

void GameObject::update()
{

}

