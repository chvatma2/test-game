#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector2D>
#include <QOpenGLTexture>

#include <spritebatch.h>

const float OBJECT_SIZE = 60;

enum class ObjectType
{
    ENEMY,
    PLAYER
};

class GameObject
{
public:
    GameObject(const QVector2D& position, GLuint texture);
    virtual ~GameObject();

    void draw(MyLE::SpriteBatch& spriteBatch);
    virtual void update() = 0;

    QVector2D getPosition() const;

protected:
    QVector2D m_Position;
    GLuint m_Texture;
    ObjectType m_Type;
};

#endif // GAMEOBJECT_H
