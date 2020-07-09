#ifndef PROVIDERQML_H
#define PROVIDERQML_H

#include <QObject>
#include <QColor>
#include <QUrl>

class ProviderQml : public QObject
{
    Q_OBJECT

    QString pathIcomButtonHome;

    Q_PROPERTY(bool isDebug                 READ    getDebug            CONSTANT)
    Q_PROPERTY(QColor colorBackground       READ    getColorBackground  CONSTANT)
    Q_PROPERTY(QString pathIcomButtonHome   MEMBER  pathIcomButtonHome  CONSTANT)
public:
    explicit ProviderQml(QObject *parent = nullptr);

    static QColor getColorBackground();
private:
    bool getDebug() const;

};

#endif // PROVIDERQML_H
