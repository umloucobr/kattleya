#include "katelleya.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Katelleya w;
    w.show();
    return a.exec();
}
