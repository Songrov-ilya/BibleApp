import QtQuick 2.0
import QtQuick.Window 2.12

Item {
    width: screenWidth
    height: screenHeight

    property real screenWidth: providerQml.isDebug ? 360 : Screen.width
    property real screenHeight: providerQml.isDebug ? 640 : Screen.height

    QmlMain{
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
    }

    MouseArea{
        anchors.fill: parent
        propagateComposedEvents: true
        onPressed: mouse.accepted = false
        onDoubleClicked: Qt.quit()
    }


}
