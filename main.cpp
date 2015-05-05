#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    GLWidget glwindow;

    glwindow.show();

    return app.exec();
}
