#ifndef MAINGAME_H
#define MAINGAME_H

#include <QApplication>
#include <QScreen>

#include <glwidget.h>

class MainGame : public QObject
{
   Q_OBJECT

public:
    MainGame();
    ~MainGame();
    void init();
    void initTimers(int swapInterval);
    void initWindow(int minWidth, int minHeight, bool fullScreen);
    void connectSlots();

private:
    MyLE::GLWidget* m_window;
    QTimer* m_frameTimer;

public slots:
    void update();
};

#endif // MAINGAME_H
