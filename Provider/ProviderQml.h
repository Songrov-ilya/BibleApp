#ifndef PROVIDERQML_H
#define PROVIDERQML_H

#include <QObject>

class ProviderQml : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isDebug READ getDebug CONSTANT)
public:
    explicit ProviderQml(QObject *parent = nullptr);


private:
    bool getDebug() const;

};

#endif // PROVIDERQML_H
