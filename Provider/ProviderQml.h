#ifndef PROVIDERQML_H
#define PROVIDERQML_H

#include <QObject>
#include <QColor>

class ProviderQml : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isDebug READ getDebug CONSTANT)
    Q_PROPERTY(QColor colorBackground READ getColorBackground CONSTANT)
public:
    explicit ProviderQml(QObject *parent = nullptr);

    static QColor getColorBackground();
private:
    bool getDebug() const;

};

#endif // PROVIDERQML_H
