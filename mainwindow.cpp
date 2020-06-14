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
//    setColor("#00000000");
    setColor("#292420");

//    qmlRegisterType<ProviderQml>("ProviderQml.Bible", 1, 1, "ProviderQml");
//    qRegisterMetaType<ProviderQml>("providerQml");
    qmlRegisterUncreatableMetaObject(
                BibleSlide::staticMetaObject, // static meta object
                "bible.namespace",                // import statement (can be any string)
                1, 0,                          // major and minor version of the import
                "BibleSlide",                 // name in QML (does not have to match C++ name)
                "Error: only enums"            // error in case someone tries to create a MyNamespace object
                );
    qRegisterMetaType<BibleSlide::Slide>("BibleSlide::Slide"); // not qmlRegister but qRegister

    rootContext()->setContextProperty("providerQml", &providerQml);
    setSource(QUrl::fromLocalFile("../BibleApp/QmlFiles/mainQml.qml"));
//    setSource(QUrl("qrc:/QmlFiles/QmlFiles/mainQml.qml"));
    connect(this->engine(), &QQmlEngine::quit, this, &QCoreApplication::quit);
}

