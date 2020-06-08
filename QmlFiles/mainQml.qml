import QtQuick 2.0
import QtQuick.Window 2.12

Item {
    width: providerQml.isDebug ? 360 : Screen.width
    height: providerQml.isDebug ? 640 : Screen.height

    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.5
    }

    QmlTitleSlide{
        anchors.fill: parent
    }



    MouseArea{
        anchors.fill: parent
        propagateComposedEvents: true
        onPressed: mouse.accepted = false
        onDoubleClicked: Qt.quit()
    }
}
