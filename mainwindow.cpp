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

void MainWindow::setGeneralSettings()
{
//    setColor("#00000000");
    setColor("#292420");


//    rootContext()->setContextProperty("providerQml", &providerQml);
//    setSource(QUrl::fromLocalFile("../BibleApp/QmlFiles/mainQml.qml"));
    setSource(QUrl("qrc:/QmlFiles/QmlFiles/rootQml.qml"));
    connect(this->engine(), &QQmlEngine::quit, this, &QCoreApplication::quit);
}

