#include "Manager.h"

Manager::Manager(QQmlContext *rootContext, QObject *parent) :
    QObject(parent),
    rootContext(rootContext),
    m_elapsed(0)
{
    setQmlSettings();
}

void Manager::setCurrentTestament(const BibleEnums::Testament &testament)
{
    bible.setCurrentTestament(testament);
}

void Manager::setCurrentBook(const QString &book)
{
    bible.setCurrentBook(book);
}

void Manager::setCurrentChapter(const int &chapter)
{
    qDebug() << "chapter" << chapter << Qt::endl;
    bible.setCurrentChapter(chapter);
}

void Manager::fillListBooks()
{
    listBooks.setList(bible.getListBooks());
}

void Manager::fillListChapters()
{
    listChapters.setList(bible.getListQuantityChapters());
}

void Manager::fillListVerses()
{
    listVerses.setList(bible.getListVerses());
}

void Manager::setElapsed(const int elapsed)
{
    m_elapsed = elapsed;
}

int Manager::getElapsed()
{
    return m_elapsed;
}

void Manager::setQmlSettings()
{
    qmlRegisterType<ModelView>("ModelViewQml", 1, 0, "ModelView");
    rootContext->setContextProperty("listBooksQml", &listBooks);
    rootContext->setContextProperty("listChaptersQml", &listChapters);
    rootContext->setContextProperty("listVersesQml", &listVerses);
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
