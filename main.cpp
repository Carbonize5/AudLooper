#include "audlooperwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AudLooperWindow w;
    w.show();
    return a.exec();
}
