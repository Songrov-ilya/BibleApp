#include "Manager.h"

Manager::Manager(QQmlContext *rootContext, QObject *parent) :
    QObject(parent),
    rootContext(rootContext)
{
    setQmlSettings();
}

void Manager::fillListChapters(const BibleEnums::Testament testament)
{

    listChapters.appendList(bible.getListAllBooks());
}

void Manager::fillListNumberVerses(const BibleEnums::Testament testament)
{

}

void Manager::fillListVerses(const BibleEnums::Testament testament)
{

}

void Manager::setQmlSettings()
{
    qmlRegisterType<ModelView>("ModelViewQml", 1, 0, "ModelView");
    rootContext->setContextProperty("listChaptersQml", &listChapters);
    rootContext->setContextProperty("listChaptersQml", &listNumberVerses);
    rootContext->setContextProperty("listChaptersQml", &listVerses);
    qmlRegisterUncreatableMetaObject(
                BibleEnums::staticMetaObject, // static meta object
                "bible.namespace",                // import statement (can be any string)
                1, 0,                          // major and minor version of the import
                "BibleEnums",                 // name in QML (does not have to match C++ name)
                "Error: only enums"            // error in case someone tries to create a MyNamespace object
                );
    qRegisterMetaType<BibleEnums::Slide>("BibleEnums::Slide"); // not qmlRegister but qRegister
    qRegisterMetaType<BibleEnums::Testament>("BibleEnums::Testament"); // not qmlRegister but qRegister

    rootContext->setContextProperty("providerQml", &providerQml);
}
