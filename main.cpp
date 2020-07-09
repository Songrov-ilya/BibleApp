#include "mainwindow.h"


#include <QElapsedTimer>
#include <QApplication>


int main(int argc, char *argv[])
{
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
#ifdef QT_NO_DEBUG
    Q_INIT_RESOURCE(ResourceFiles);
#endif
    MainWindow w;
    w.show();

    w.setElapsed(elapsedTimer.elapsed());
    qDebug() << "elapsedTimer.elapsed()" << elapsedTimer.elapsed() << Qt::endl;
    return a.exec();
}
