#include "maingame.h"

//Constants definition
const float SCALE_SPEED = 0.1f;
const float CAMERA_SPEED = 2.0f;

MainGame::MainGame(QWidget *parent)
    : QOpenGLWidget(parent), m_FrameCounter(0), m_Player(nullptr), m_ClearColor(Qt::darkGray), m_CurrentLevel(0)
{

}

MainGame::~MainGame()
{
    delete m_MainCamera;
    for(unsigned int i = 0; i < m_Levels.size(); i++)
        delete m_Levels[i];
    for(unsigned int i = 0; i< m_Objects.size(); i++)
        delete m_Objects[i];
}

void MainGame::connectSlots()
{
    //Frame render signal
    connect(&m_FrameTimer, SIGNAL(timeout()), this, SLOT(update()));

    //FPS print signal
    connect(&m_FPSTimer, SIGNAL(timeout()), this, SLOT(printFPS()));

    //Input signals
    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), &m_InputManager, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(keyReleaseEvent(QKeyEvent*)), &m_InputManager, SLOT(keyReleased(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), &m_InputManager, SLOT(mouseMoved(QMouseEvent*)));
    connect(this, SIGNAL(mousePressEvent(QMouseEvent*)), &m_InputManager, SLOT(mouseButtonPressed(QMouseEvent*)));
    connect(this, SIGNAL(mouseReleaseEvent(QMouseEvent*)), &m_InputManager, SLOT(mouseButtonReleased(QMouseEvent*)));
}

//MAIN GAME LOOP
void MainGame::paintGL()
{
    processInput();

    gameLogic();

    renderGame();

    updateTimers();
}

void MainGame::initializeGL()
{
    initializeOpenGLFunctions();

    //Enable use of alpha channel for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Print info
    qDebug() << "Opengl version: " << (char*)glGetString(GL_VERSION);
    qDebug() << "Height: " << height();
    qDebug() << "Width: " << width();

    this->setMouseTracking(true);

    initShaders();

    m_MainCamera->setScreenSize(width(), height());

    m_SpriteBatch.init(&m_Shader, &m_ResourceManager);

    m_FrameTimer.start();
    m_FPSTimer.start();


    //Read game data
    readLevels();
    initPlayer();
}

void MainGame::processInput()
{
    if(m_InputManager.isKeyPressed(Qt::Key_Q))
        m_MainCamera->changeScaleBy(SCALE_SPEED);
    if(m_InputManager.isKeyPressed(Qt::Key_E))
        m_MainCamera->changeScaleBy(-SCALE_SPEED);
    if(m_InputManager.isButtonPressed(Qt::LeftButton))
    {
        QVector2D clickPosition = m_MainCamera->convertScreenPosition(m_InputManager.getMousePosition());

        QVector2D playerPosition(0.0f, 0.0f);
        QVector2D direction(clickPosition - playerPosition);
        QVector2D size(10.0f, 10.0f);
        direction.normalize();
    }
}

void MainGame::gameLogic()
{
    for(unsigned int i = 0; i < m_Objects.size(); i++)
        m_Objects[i]->update();
}

void MainGame::renderGame()
{
    renderGameBegin();

    renderGameDraw();

    renderGameEnd();
}

void MainGame::renderGameBegin()
{
    m_MainCamera->setPosition(m_Player->getPosition());
    m_MainCamera->update();

    glClearColor(m_ClearColor.redF(), m_ClearColor.greenF(), m_ClearColor.blueF(), m_ClearColor.alphaF());
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(m_Shader.uniformLocation("testTexture"), 0);

    m_Shader.setUniformValue("time", m_Time);
    m_Shader.setUniformValue("P", m_MainCamera->getViewMatrix());

    glActiveTexture(GL_TEXTURE0);

    m_SpriteBatch.begin();
}

void MainGame::renderGameDraw()
{
    m_Levels[m_CurrentLevel]->draw();

    for(unsigned int i = 0; i < m_Objects.size(); i++)
        m_Objects[i]->draw(m_SpriteBatch);
}

void MainGame::renderGameEnd()
{
    m_SpriteBatch.end();
    m_SpriteBatch.renderBatch();
}


void MainGame::init()
{
    //System config
    QSurfaceFormat format;
    format.setSwapInterval(1);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);

    initTimers(format.swapInterval());
    initWindow(1600, 900);
    connectSlots();
}

void MainGame::initTimers(int swapInterval)
{
    //If VSYNC is enabled, let it handle the repaint, otherwise set frame timer to fit screen refresh rate
    m_FrameTimer.setTimerType(Qt::PreciseTimer);
    qreal refreshRate = QApplication::screens().at(0)->refreshRate();
    if(swapInterval == -1)
    {
        qDebug() << "VSYNC disabled";
        m_FrameTimer.setInterval(1000.0/refreshRate);
    }
    else
    {
        qDebug() << "VSYNC enabled";
        m_FrameTimer.setInterval(0);
    }

    //Set fps print delay to 5 seconds
    m_FPSTimer.setInterval(5000);
}

void MainGame::updateTimers()
{
    m_FrameCounter++;
    m_Time += 0.01f;
}

void MainGame::initShaders()
{
    if( m_Shader.addShaderFromSourceFile(QOpenGLShader::Vertex, "resources/shaders/vertshader.vert"))
        qDebug() << "Vertex shader compiled succesfuly";
    if (m_Shader.addShaderFromSourceFile(QOpenGLShader::Fragment, "resources/shaders/fragshader.frag"))
        qDebug() << "Fragment shader compiled succesfuly";
    m_Shader.bindAttributeLocation("vertexPosition", 0);
    m_Shader.bindAttributeLocation("vertexColor", 1);
    m_Shader.bindAttributeLocation("vertexUV", 2);
    m_Shader.link();
    m_Shader.bind();
    m_Shader.setUniformValue("testTexture", 0);
}

void MainGame::initPlayer()
{
    m_Player = new Player(m_Levels[m_CurrentLevel]->getPlayerPosition(),
                          m_ResourceManager.loadTexture("resources/textures/starwars/xwing.png"),
                          10.0f,
                          &m_InputManager);
    m_Objects.push_back(m_Player);
}

void MainGame::initWindow(int width, int height)
{
    setFixedSize(width, height);

    initCameras();
}

void MainGame::initCameras()
{
    m_MainCamera = new MyLE::Camera2D(width(), height());
}

void MainGame::readLevels()
{
    m_Levels.push_back(new Level("resources/levels/level1", &m_ResourceManager, &m_Shader));
}

void MainGame::printFPS()
{
    qDebug() << "FPS: " << m_FrameCounter/5;
    m_FrameCounter = 0;
}

void MainGame::update()
{
    repaint();
}
