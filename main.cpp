#include "mainwindow.h"
#include "customframe.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomFrame f(new MainWindow(argc, argv));
//    f.setMinimumWidth(400);


    static QIcon icon(":/starflower.png");
    f.resize(420, 400);
    f.show();
    f.setWindowIcon(icon);
    return a.exec();
}
