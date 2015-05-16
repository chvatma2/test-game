#include "level.h"

Level::Level(const QString& fileName, MyLE::ResourceManager* resourceManager, QOpenGLShaderProgram* program)
    : m_ResourceManager(resourceManager), m_ShaderProgram(program)
{
    QFile levelFile(fileName);

    if(!levelFile.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Failed to open level " + fileName;

    QTextStream levelStream(&levelFile);

    QString temp;

    levelStream >> temp >> m_EnemiesCount;
    levelStream.skipWhiteSpace();

    while(!levelStream.atEnd())
    {
        m_LevelData.push_back(levelStream.readLine().toStdString());
    }

    m_SpriteBatch.init(m_ShaderProgram, m_ResourceManager);
    m_SpriteBatch.begin();

    QVector4D uv(0.0f, 0.0f, 1.0f, 1.0f);
    QColor color(255, 255, 255, 255);

    GLuint fireTexture = m_ResourceManager->loadTexture("resources/textures/starwars/fire.png");
    GLuint spaceTexture = m_ResourceManager->loadTexture("resources/textures/starwars/stars-background-purple.png");

    for(unsigned int y = 0; y < m_LevelData.size(); y++)
    {
        for(unsigned int x = 0; x < m_LevelData[y].size(); x++)
        {
            QVector4D destination(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

            char tile = m_LevelData[y][x];

            switch(tile)
            {
            case 'R':
                m_SpriteBatch.draw(destination,
                                   uv,
                                   fireTexture,
                                   0.0f,
                                   color);
                break;
            case '.':
                m_SpriteBatch.draw(destination,
                                   uv,
                                   spaceTexture,
                                   0.0f,
                                   color);
                break;
            case '@':
                m_PlayerPosition.setX(x * TILE_SIZE);
                m_PlayerPosition.setY(y * TILE_SIZE);
                m_SpriteBatch.draw(destination,
                                   uv,
                                   spaceTexture,
                                   0.0f,
                                   color);
                break;
            case '!':
                m_EnemyPositions.emplace_back(x * TILE_SIZE, y * TILE_SIZE);
                m_SpriteBatch.draw(destination,
                                   uv,
                                   spaceTexture,
                                   0.0f,
                                   color);
                break;
            default:
                qDebug() << "Unexpected symbol in level file " + fileName;

            }
        }
    }
    m_SpriteBatch.end();
}


void Level::debugDraw()
{
    //foreach(const QString& str, m_LevelData)
    //    qDebug() << str;
}

void Level::draw()
{
    m_SpriteBatch.renderBatch();
}

QVector2D Level::getPlayerPosition() const
{
    return m_PlayerPosition;
}

const std::vector<QVector2D> &Level::getEnemyPositions() const
{
    return m_EnemyPositions;
}

