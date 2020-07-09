#include "ProviderQml.h"

ProviderQml::ProviderQml(QObject *parent) :
    QObject(parent),
    pathIcomButtonHome("qrc:/Icons/Resource/Icons/iconfinder_20-blue_address-home-house_4488794.svg")
{
#ifdef QT_DEBUG
    pathIcomButtonHome = QUrl::fromLocalFile("../BibleApp/Resource/Icons/iconfinder_20-blue_address-home-house_4488794.svg").toString();
#endif
}

bool ProviderQml::getDebug() const
{
    bool isDebug { false };
#ifdef QT_DEBUG
    isDebug = true;
#endif
    return isDebug;
}

QColor ProviderQml::getColorBackground()
{
    return QColor("#292420");
}
