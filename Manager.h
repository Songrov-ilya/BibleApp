#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>

#include "Provider/ProviderQml.h"
#include "Achitecture/Bible.h"
#include "Extensions/Data.h"
#include "View/ModelView.h"
#include "View/BibleList.h"

class Manager : public QObject
{
    Q_OBJECT

    QQmlContext *rootContext;
    ProviderQml providerQml;
    Bible bible;
    BibleList listBooks;
    BibleList listChapters;
    BibleList listVerses;
    int m_elapsed;
public:
    explicit Manager(QQmlContext *rootContext, QObject *parent = nullptr);

    Q_INVOKABLE void setCurrentTestament(const BibleEnums::Testament testament);
    Q_INVOKABLE void setCurrentBook(const int numberBook);
    Q_INVOKABLE void setCurrentChapter(const int &chapter);
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
