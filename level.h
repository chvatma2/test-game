#ifndef LEVEL_H
#define LEVEL_H

#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QDebug>

#include <spritebatch.h>
#include <resourcemanager.h>

const int TILE_SIZE = 64;

class Level
{
public:
    Level(const QString &fileName, MyLE::ResourceManager *resourceManager, QOpenGLShaderProgram *program);

    void draw();
    QVector2D getPlayerPosition() const;
    const std::vector<QVector2D>& getEnemyPositions() const;

private:
    std::vector<std::string> m_LevelData;
    void debugDraw();

    int m_EnemiesCount;
    QVector2D m_PlayerPosition;
    std::vector<QVector2D> m_EnemyPositions;
    MyLE::SpriteBatch m_SpriteBatch;
    MyLE::ResourceManager* m_ResourceManager;
    QOpenGLShaderProgram* m_ShaderProgram;
};

#endif // LEVEL_H
