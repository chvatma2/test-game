#include <QApplication>
#include "maingame.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("MyLE");

    MainGame game;
    game.init();

    return app.exec();
}
