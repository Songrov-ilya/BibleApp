#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>

#include "ProviderQml.h"
#include "Bible.h"
#include "Data.h"
#include "Search.h"
#include "ModelView.h"
#include "BibleList.h"

class Manager : public QObject
{
    Q_OBJECT

    QQmlContext *rootContext;
    ProviderQml providerQml;
    Bible bible;
    Search search;
    BibleList listBooks;
    BibleList listChapters;
    BibleList listVerses;
    BibleList listSearch;
    int m_elapsed;

public:
    explicit Manager(QQmlContext *rootContext, QObject *parent = nullptr);

    Q_INVOKABLE QString getCurrentNameBook();

    Q_INVOKABLE void setCurrentTestament(const BibleEnums::Testament testament);
    Q_INVOKABLE void setCurrentBook(const int indexBook);
    Q_INVOKABLE void setCurrentChapter(const int indexChapter);
    Q_INVOKABLE void fillListBooks();
    Q_INVOKABLE void fillListChapters();
    Q_INVOKABLE void fillListVerses();

    void setElapsed(const int elapsed);
    Q_INVOKABLE int getElapsed();
private:
    void setQmlSettings();
    void loadListBooks();

};

#endif // MANAGER_H
