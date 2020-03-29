#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

namespace File {
    const QString newTestament_Content = "../BibleApp/Other/NewTestament_Content.json";
    const QString oldTestament_Content = "../BibleApp/Other/OldTestament_Content.json";
    const QString bibleTextJson = "../BibleApp/TextBible/Bible_XML_and_JSON/bible-master/json/ru_synodal.json";
}

class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

    static void readFileJson(const QString path, QJsonDocument &doc);
    static QJsonDocument readFileJson(const QString path);
    static void writeFileJson(const QString path, const QJsonDocument &doc);
};

#endif // HELPER_H
