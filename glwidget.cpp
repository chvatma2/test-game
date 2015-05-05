#include "glwidget.h"
#include <QScreen>
#include <QApplication>
#include <iostream>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), m_shader(0), m_time(0), m_clearColor(Qt::darkBlue), m_frameCounter(0)
{
    m_inputManager = new InputManager(this);
    QSurfaceFormat f = this->format();
    f.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    f.setSwapInterval(1);
    this->setFormat(f);
    setMinimumSize(200, 200);
}

GLWidget::~GLWidget()
{
    makeCurrent();

    foreach (Sprite* s, m_sprites)
        delete s;
    delete m_shader;

    doneCurrent();
}

void GLWidget::setClearColor(const QColor &color)
{
    m_clearColor = color;
    update();
}

void GLWidget::paintGL()
{
    glClearColor(m_clearColor.redF(), m_clearColor.greenF(), m_clearColor.blueF(), m_clearColor.alphaF());
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(m_shader->uniformLocation("testTexture"), 0);

    m_time += 0.01f;
    m_shader->setUniformValue("time", m_time);

    foreach (Sprite* s, m_sprites)
    {
        s->draw(m_shader);
    }

    m_frameCounter++;
}

void GLWidget::resizeGL(int w, int h)
{
    this->resize(w, h);
}

void GLWidget::connectSlotsSignals()
{
    connect(&m_redrawTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    connect(&m_fpsTimer, SIGNAL(timeout()), this, SLOT(printFPS()));
    connect(this, SIGNAL(keyPressEvent(QKeyEvent*)), m_inputManager, SLOT(keyPressed(QKeyEvent*)));
    connect(this, SIGNAL(keyReleaseEvent(QKeyEvent*)), m_inputManager, SLOT(keyReleased(QKeyEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), m_inputManager, SLOT(mouseMoved(QMouseEvent*)));
}

void GLWidget::initScreen()
{
    QScreen* currentScreen = QApplication::screens().at(0);
    resizeGL(currentScreen->availableGeometry().width(), currentScreen->availableGeometry().height());
    m_refreshRate = currentScreen->refreshRate();
}

void GLWidget::initTimers()
{
    m_redrawTimer.setTimerType(Qt::PreciseTimer);
    m_fpsTimer.setTimerType(Qt::PreciseTimer);

    if(format().swapInterval() == -1)
    {
        qDebug() << "Swap interval -1";
        m_redrawTimer.setInterval(1000/m_refreshRate);
    }
    else
    {
        m_redrawTimer.setInterval(0);
    }
    m_fpsTimer.setInterval(5000);

    m_redrawTimer.start();
    m_fpsTimer.start();

}

void GLWidget::initShaders()
{
    m_shader = new QOpenGLShaderProgram(this);
    if( m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertshader.vert"))
        qDebug() << "Vertex shader compiled succesfuly";
    if (m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragshader.frag"))
        qDebug() << "Fragment shader compiled succesfuly";
    m_shader->bindAttributeLocation("vertexPosition", 0);
    m_shader->bindAttributeLocation("vertexColor", 1);
    m_shader->bindAttributeLocation("vertexUV", 2);
    m_shader->link();
    m_shader->bind();
    m_shader->setUniformValue("testTexture", 0);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    qDebug() << "Opengl version: " << (char*)glGetString(GL_VERSION);

    initScreen();
    connectSlotsSignals();
    initTimers();

    this->setMouseTracking(true);

    initShaders();

    //m_resourceManager.loadTexture(":/CharacterRight_Standing.png", m_testTexture);

    m_sprites.push_back(new Sprite(0.0f, 0.0f, 1.0f, 1.0f, ":/textures/JimmyJump/CharacterRight_Standing.png", m_resourceManager));
    m_sprites.push_back(new Sprite(-1.0f, 0.0f, 1.0f, 1.0f, ":/textures/JimmyJump/CharacterRight_Standing.png", m_resourceManager));
}

void GLWidget::refresh()
{
    repaint();
}

void GLWidget::printFPS()
{
    qDebug() << "FPS: " << m_frameCounter/5;
    m_frameCounter = 0;
}
