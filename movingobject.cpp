#include "movingobject.h"

MovingObject::MovingObject(const QVector2D &position, GLuint texture, float speed)
    : GameObject(position, texture), m_Speed(speed)
{

}

MovingObject::~MovingObject()
{

}

void MovingObject::update(const std::vector<std::string> &levelData, std::vector<GameObject *> objects)
{

}

void MovingObject::collideWithLevel(const std::vector<std::string> &levelData)
{

}

void MovingObject::collideWithObjects(std::vector<GameObject *> objects)
{

}

