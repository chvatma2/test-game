#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "gameobject.h"

class MovingObject : public GameObject
{
public:
    MovingObject(const QVector2D& position, GLuint texture, float speed);
    virtual ~MovingObject();

    virtual void update(const std::vector<std::string>& levelData, std::vector<GameObject*> objects);


protected:
    float m_Speed;
    void collideWithLevel(const std::vector<std::string>& levelData);
    void collideWithObjects(std::vector<GameObject*> objects);
};

#endif // MOVINGOBJECT_H
