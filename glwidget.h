#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QColor>
#include "inputmanager.h"
#include "sprite.h"
#include "vertex.h"
#include "resourcemanager.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;

    void setClearColor(const QColor& color);

private slots:
    void refresh();
    void printFPS();

private:
    qreal m_refreshRate;
    QTimer m_redrawTimer;
    QTimer m_fpsTimer;
    InputManager* m_inputManager;
    QOpenGLShaderProgram * m_shader;
    GLfloat m_time;
    QColor m_clearColor;

    ResourceManager m_resourceManager;
    QOpenGLTexture * m_testTexture;

    int m_frameCounter;
    QVector<Sprite*> m_sprites;


    void connectSlotsSignals();
    void initScreen();
    void initTimers();
    void initShaders();


signals:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // GLWIDGET_H
