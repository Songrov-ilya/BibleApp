#include "mainwindow.h"


MainWindow::MainWindow(QWindow *parent)
    : QQuickView(parent),
      manager(nullptr)
{
    QSize sizeScreen = QGuiApplication::primaryScreen()->availableSize() * 3 / 5;
    resize(sizeScreen.width(), sizeScreen.height());
#ifdef QT_DEBUG
    resize(360, 640);
#endif

    manager = new Manager(rootContext());
    setGeneralSettings();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setElapsed(const int elapsed)
{
    manager->setElapsed(elapsed);
}

void MainWindow::setGeneralSettings()
{
//    setColor("#00000000");
    setColor(ProviderQml::getColorBackground());


    rootContext()->setContextProperty("managerQml", manager);
#ifdef QT_DEBUG
    setSource(QUrl::fromLocalFile("../BibleApp/QmlFiles/rootQml.qml"));
#else
    setSource(QUrl("qrc:/QmlFiles/QmlFiles/rootQml.qml"));
#endif
    connect(this->engine(), &QQmlEngine::quit, this, &QCoreApplication::quit);
}

