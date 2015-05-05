#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    GLWidget glwindow;

    glwindow.show();

    return app.exec();
}
