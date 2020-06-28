#ifndef HELPER_H
#define HELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

class Helper
{

public:
    explicit Helper();

    static void readFileJson(QJsonDocument *doc, const QString &path);
    static QJsonDocument readFileJson(const QString &path);
    static void writeFileJson(const QJsonDocument &doc, const QString &path);

    static QString getNumberStr(const int num);
};

#endif // HELPER_H
