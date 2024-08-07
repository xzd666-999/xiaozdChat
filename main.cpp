#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly))
    {
        QString style =QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
