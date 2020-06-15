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
    BibleList listChapters;
    BibleList listNumberVerses;
    BibleList listVerses;
public:
    explicit Manager(QQmlContext *rootContext, QObject *parent = nullptr);

    Q_INVOKABLE void fillListChapters(const BibleEnums::Testament testament);
    Q_INVOKABLE void fillListNumberVerses(const BibleEnums::Testament testament);
    Q_INVOKABLE void fillListVerses(const BibleEnums::Testament testament);
private:
    void setQmlSettings();
};

#endif // MANAGER_H
