#include "peer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Peer w;
    w.show();

    return a.exec();
}
