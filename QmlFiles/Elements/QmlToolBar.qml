import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import QtQuick.Controls.Material 2.15

import "../Components" as MyComonents
import bible.namespace 1.0

ToolBar{
    id: toolBarMenu

    position: ToolBar.Header
    RowLayout {
        anchors.fill: parent
        ToolButton {
            text: qsTr("‹")
            onClicked: stack.pop()
        }
        Label {
            text: "Title"
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }
        ToolButton {
            Material.foreground: Material.LightBlue
            id: toolButtonBook
            icon.source: "../../Resource/Icons/Include_link_iconfinder_LIBRARY_2_753918.svg"
            contentItem: Item {
                anchors.fill: parent
                Image {
                    id : menuButtonIcon
                    source: toolButtonBook.icon.source
                    width: toolButtonBook.icon.width
                    height: toolButtonBook.icon.height
                    anchors.centerIn: parent

                    ColorOverlay {
                        anchors.fill: menuButtonIcon
                        source: menuButtonIcon
                        color: Material.color(Material.Grey)
                    }
                }
            }
        }
        ToolButton {
            text: qsTr("⋮")
            //                onClicked: menu.open()
        }
    }
}
