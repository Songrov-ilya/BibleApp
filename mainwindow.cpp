#include "mainwindow.h"


MainWindow::MainWindow(QWindow *parent)
    : QQuickView(parent)
{
    QSize sizeScreen = QGuiApplication::primaryScreen()->availableSize() * 3 / 5;
    resize(sizeScreen.width(), sizeScreen.height());
#ifdef QT_DEBUG
    resize(360, 640);
#endif

    setQmlSettings();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setQmlSettings()
{
//    qmlRegisterType<ProviderQml>("ProviderQml.Bible", 1, 1, "ProviderQml");
//    qRegisterMetaType<ProviderQml>("providerQml");

    rootContext()->setContextProperty("providerQml", &providerQml);
    setSource(QUrl::fromLocalFile("../BibleApp/QmlFiles/mainQml.qml"));
    connect(this->engine(), &QQmlEngine::quit, this, &QCoreApplication::quit);
}

