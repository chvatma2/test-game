#include <QApplication>
#include "maingame.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Test Game");

    MainGame game;
    game.init();
    game.show();

    return app.exec();
}
