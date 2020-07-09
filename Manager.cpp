#include "Manager.h"

Manager::Manager(QQmlContext *rootContext, QObject *parent) :
    QObject(parent),
    rootContext(rootContext),
    providerQml(),
    bible(),
    search(&bible),
    m_elapsed(0)
{
    setQmlSettings();
}

QString Manager::getCurrentNameBook()
{
//    return bible.getCurrentBook()->getNameBook();
    if (listBooks.getSize() <= 0) {
        return "nothing";
    }
    return listBooks.getText(bible.getCurrentIndexBook());
}

void Manager::setCurrentTestament(const BibleEnums::Testament testament)
{
    bible.setCurrentTestament(testament);
}

void Manager::setCurrentBook(const int indexBook)
{
    bible.setCurrentBook(indexBook);
}

void Manager::setCurrentChapter(const int indexChapter)
{
    qDebug() << "chapter" << indexChapter << Qt::endl;
    bible.setCurrentChapter(indexChapter);
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
    rootContext->setContextProperty("listSearchQml", &listSearch);
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
