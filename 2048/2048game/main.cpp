#include "board.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board board(700, 900);
    board.show();

    return a.exec();
}
