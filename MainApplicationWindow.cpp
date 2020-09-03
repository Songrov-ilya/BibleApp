#include "MainApplicationWindow.h"


MainApplicationWindow::MainApplicationWindow(QObject *parent)
    : QQmlApplicationEngine(parent)
    ,  manager(nullptr)
{
    manager = new Manager(rootContext());
    setGeneralSettings();
}

MainApplicationWindow::~MainApplicationWindow()
{

}

void MainApplicationWindow::setElapsed(const int elapsed)
{
    manager->setElapsed(elapsed);
}

void MainApplicationWindow::setGeneralSettings()
{
    rootContext()->setContextProperty("managerQml", manager);
    QUrl url = QUrl("qrc:/QmlFiles/QmlFiles/rootQml.qml");
#ifdef QT_DEBUG
    url = QUrl::fromLocalFile("../BibleApp/QmlFiles/rootQml.qml");
#endif
    connect(this, &QQmlApplicationEngine::quit, this, &QCoreApplication::quit);
    connect(this, &QQmlApplicationEngine::objectCreated, this, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl){
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    this->load(url);
}

