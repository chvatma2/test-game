#include "enemy.h"

Enemy::Enemy(const QVector2D &position, GLuint texture, float speed)
    : Ship(position, texture, speed)
{
    m_Type = ObjectType::ENEMY;
}

Enemy::~Enemy()
{

}

