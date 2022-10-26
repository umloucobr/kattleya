#include "katlleya.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Katlleya w;
    w.show();
    return a.exec();
}
