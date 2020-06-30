#include "Helper.h"

Helper::Helper()
{

}

void Helper::readFileJson(QJsonDocument *doc, const QString &path)
{
    QJsonParseError error;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    *doc = QJsonDocument::fromJson(file.readAll(), &error);
    file.close();
}

QJsonDocument Helper::readFileJson(const QString &path)
{
    QJsonDocument doc;
    readFileJson(&doc, path);
    return doc;
}

void Helper::writeFileJson(const QJsonDocument &doc, const QString &path)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)){
        qDebug() << "Error WriteOnly file" << path << Qt::endl;
        return;
    }
    file.write(doc.toJson());
    file.close();
}

