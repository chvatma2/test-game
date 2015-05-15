#ifndef MAINGAME_H
#define MAINGAME_H

#include <QApplication>
#include <QScreen>
#include <QOpenGLWidget>
#include <QTimer>

#include <camera2d.h>
#include <inputmanager.h>
#include <resourcemanager.h>
#include <spritebatch.h>

#include "projectile.h"


class MainGame : public QOpenGLWidget, protected QOpenGLFunctions
{
   Q_OBJECT

public:
    explicit MainGame(QWidget* parent = 0);
    ~MainGame();

    void init();
    void connectSlots();

    void paintGL() Q_DECL_OVERRIDE;
//    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;

private:
    //Main components
    void processInput();
    void gameLogic();
    void renderGame();
    MyLE::InputManager m_InputManager;
    MyLE::ResourceManager m_ResourceManager;
    MyLE::SpriteBatch m_SpriteBatch;

    //Timers
    void initTimers(int swapInterval);
    QTimer m_FrameTimer;
    QTimer m_FPSTimer;
    GLfloat m_Time;
    int m_FrameCounter;

    //Cameras
    MyLE::Camera2D* m_MainCamera;

    //Shaders
    void initShaders();
    QOpenGLShaderProgram m_Shader;

    QOpenGLTexture * m_TestTexture;


    //Game objects
    std::vector<Projectile> m_Projectiles;

    //Config
    void initWindow(int width, int height);
    void initCameras();
    QColor m_ClearColor;


private slots:
    void printFPS();
    void update();

signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // MAINGAME_H
