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
    const QString NewTestament_Content = "../BibleApp/Other/NewTestament_Content.json";
    const QString OldTestament_Content = "../BibleApp/Other/OldTestament_Content.json";
}
class Helper : public QObject
{
    Q_OBJECT
public:
    explicit Helper(QObject *parent = nullptr);

    static void readFileJson(const QString path, QJsonDocument &doc);
    static QJsonDocument readFileJson(const QString path);
    static void writeFileJson(const QString path, QJsonDocument &doc);
};

#endif // HELPER_H
