#include "MainApplicationWindow.h"


#include <QElapsedTimer>
#include <QApplication>
#include <QQuickStyle>


int main(int argc, char *argv[])
{
    QElapsedTimer elapsedTimer;
    elapsedTimer.start();

    QQuickStyle::setStyle("Material");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
#ifdef QT_NO_DEBUG
    Q_INIT_RESOURCE(ResourceFiles);
#endif


    MainApplicationWindow w;

    w.setElapsed(elapsedTimer.elapsed());
    qDebug() << "elapsedTimer.elapsed()" << elapsedTimer.elapsed() << Qt::endl;
    return a.exec();
}
