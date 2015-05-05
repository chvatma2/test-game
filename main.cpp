#include <QApplication>
#include "maingame.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("MyLE");

    MainGame game;
    game.init(200, 200);
    return app.exec();
}
