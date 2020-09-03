import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12
import QtGraphicalEffects 1.0

import "../Components" as MyComonents
import bible.namespace 1.0


Drawer {
    id: drawer
    width: minSideWindow * 0.66
    height: parent.height

//    position: 1 // for debug
//    visible: true // for debug

    edge: Qt.LeftEdge
    modal: Popup.CloseOnEscape
    //    y: overlayHeader.height

    ListView {
        id: listView
        anchors.fill: parent

        model: 10
        delegate: ItemDelegate {
            text: qsTr("Title %1").arg(index + 1)
            width: parent.width
        }

        headerPositioning: ListView.OverlayHeader
        header: Pane {
            id: header
            z: 2
            width: parent.width

            Material.elevation: 2
            contentHeight: logo.height

            Image {
                id: logo
                width: parent.width
                source: "../../Resource/Icons/Include_link_iconfinder_LIBRARY_2_753918.svg"
                fillMode: Image.PreserveAspectFit
            }

            MenuSeparator {
                parent: header
                width: parent.width * 0.98
                anchors.verticalCenter: parent.bottom
                visible: !listView.atYBeginning
            }
        }

        footer: ItemDelegate {
            id: footer
            text: qsTr("Footer")
            width: parent.width

            MenuSeparator {
                parent: footer
                width: parent.width
                anchors.verticalCenter: parent.top
            }
        }
//        ScrollIndicator.vertical: ScrollIndicator { }
    }
}
