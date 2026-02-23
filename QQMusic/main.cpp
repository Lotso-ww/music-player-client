#include "qqmusic.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQMusic w;
    w.show();
    return a.exec();
}
