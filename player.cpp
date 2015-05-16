#include "player.h"

Player::Player(const QVector2D& position, GLuint texture, float speed, MyLE::InputManager *inputManager)
    : Ship(position, texture, speed), m_InputManager(inputManager)
{
    m_Type = ObjectType::PLAYER;
}

Player::~Player()
{

}

void Player::update()
{
    if(m_InputManager->isKeyPressed(Qt::Key_W))
        m_Position += QVector2D(0.0f, m_Speed);
    if(m_InputManager->isKeyPressed(Qt::Key_S))
        m_Position += QVector2D(0.0f, -m_Speed);
    if(m_InputManager->isKeyPressed(Qt::Key_A))
        m_Position += QVector2D(-m_Speed, 0.0f);
    if(m_InputManager->isKeyPressed(Qt::Key_D))
        m_Position += QVector2D(m_Speed, 0.0f);
}
