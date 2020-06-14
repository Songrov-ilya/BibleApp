#include "Helper.h"

Helper::Helper(QObject *parent) : QObject(parent)
{

}

void Helper::readFileJson(const QString path, QJsonDocument &doc)
{
    QJsonParseError error;
    QFile file;
    file.setFileName(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    doc = QJsonDocument::fromJson(file.readAll(), &error);
    file.close();
}

QJsonDocument Helper::readFileJson(const QString path)
{
    QJsonDocument doc;
    readFileJson(path, doc);
    return doc;
}

void Helper::writeFileJson(const QString path, const QJsonDocument &doc)
{
    QFile file;
    file.setFileName(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)){
        qDebug() << "Error read file" << path << Qt::endl;
        return;
    }
    file.write(doc.toJson());
    file.close();
}
