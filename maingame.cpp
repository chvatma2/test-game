#include "maingame.h"

MainGame::MainGame()
{

}

MainGame::~MainGame()
{
    delete m_window;
}

void MainGame::connectSlots()
{
    connect(m_frameTimer, SIGNAL(timeout()), this, SLOT(update()));
}

void MainGame::initTimers(int swapInterval)
{
    m_frameTimer = new QTimer(this);
    m_frameTimer->setTimerType(Qt::PreciseTimer);
    qreal refreshRate = QApplication::screens().at(0)->refreshRate();
    if(swapInterval == -1)
    {
        qDebug() << "VSYNC disabled";
        m_frameTimer->setInterval(1000.0/refreshRate);
    }
    else
    {
        qDebug() << "VSYNC enabled";
        m_frameTimer->setInterval(0);
    }
    m_frameTimer->start();
}

void MainGame::initWindow(int minWidth, int minHeight, bool fullScreen)
{
    m_window = new MyLE::GLWidget();
    m_window->setMinimumSize(QSize(minWidth, minHeight));
    if(fullScreen)
        m_window->showFullScreen();
}

void MainGame::init()
{
    QSurfaceFormat format;
    format.setSwapInterval(1);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);

    initTimers(format.swapInterval());
    initWindow(200, 200, true);

    connectSlots();

    m_window->show();
}

void MainGame::update()
{
    m_window->refresh();
}
