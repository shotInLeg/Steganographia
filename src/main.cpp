#include "steganographia.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Steganographia w;
    w.show();

    return a.exec();
}
