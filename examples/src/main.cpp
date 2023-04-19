#include "jmtestapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JmTestApp w;
    w.show();
    return a.exec();
}
