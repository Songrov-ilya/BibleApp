import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12

import "Elements" as MyElements

ApplicationWindow {
    id: rootWindow
    width: screenWidth
    height: screenHeight
    visible: true


    property real screenWidth: providerQml.isDebug ? 360 : Screen.width
    property real screenHeight: providerQml.isDebug ? 640 : Screen.height
    property real minSideWindow: Math.min(screenWidth, screenHeight)
    Material.theme: Material.Dark
    Material.accent: Material.Blue
//    Material.background: Material.Blue


    footer: MyElements.QmlToolBar{}

    MyElements.QmlSidePanel{}

    QmlSlideGridBooks{
        id: slideGridBooks
        visible: true
    }

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
