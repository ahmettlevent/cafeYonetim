#include <cafesiparis.h>
#include <customerwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CafeSiparis startWindow;

    startWindow.show();

    return a.exec();
}
