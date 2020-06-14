import QtQuick 2.0
import QtQuick.Window 2.12

Item {
    width: providerQml.isDebug ? 360 : Screen.width
    height: providerQml.isDebug ? 640 : Screen.height


    QmlRoot{
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
    }



}
