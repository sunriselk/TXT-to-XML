#include "TXT2XML.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TXT2XML w;
    w.show();
    return a.exec();
}
