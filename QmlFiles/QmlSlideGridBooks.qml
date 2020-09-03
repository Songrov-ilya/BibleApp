import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import "Components" as MyComonents
import ModelViewQml 1.0
import bible.namespace 1.0

Item {
    width: minSideWindow * 0.66
    height: parent.height
    anchors.right: parent.right

    //    Flickable {
    //        id: flickable

    //        anchors.fill: parent
    //        anchors.topMargin: overlayHeader.height
    //        anchors.leftMargin: !inPortrait ? drawer.width : undefined

    //        topMargin: 20
    //        bottomMargin: 20
    //        contentHeight: column.height

    //        Column {
    //            id: column
    //            spacing: 20
    //            anchors.margins: 20
    //            anchors.left: parent.left
    //            anchors.right: parent.right

    //            Label {
    //                font.pixelSize: 22
    //                width: parent.width
    //                elide: Label.ElideRight
    //                horizontalAlignment: Qt.AlignHCenter
    //                text: qsTr("Side Panel Example")
    //            }

    //            Label {
    //                width: parent.width
    //                wrapMode: Label.WordWrap
    //                text: qsTr("This example demonstrates how Drawer can be used as a non-closable persistent side panel.\n\n" +
    //                           "When the application is in portrait mode, the drawer is an interactive side panel that can " +
    //                           "be swiped open from the left edge. When the application is in landscape mode, the drawer " +
    //                           "and the content are laid out side by side.\n\nThe application is currently in %1 mode.").arg(inPortrait ? qsTr("portrait") : qsTr("landscape"))
    //            }
    //        }

    //        ScrollIndicator.vertical: ScrollIndicator { }
    //    }

    Flickable {
        id: flickable

        anchors.fill: parent
//                anchors.topMargin: overlayHeader.height
//                anchors.leftMargin: !inPortrait ? drawer.width : undefined

        topMargin: 20
        bottomMargin: 20
//        contentHeight: gridBooks.height
        Rectangle{
            anchors.fill: parent
            color: "red"
            opacity: 0.5
        }

        MyComonents.QmlComponentGridView{
            id: gridBooks
            anchors.fill: parent
            listModelObj: ModelView {
                list: listBooksQml
            }
            colorCell      : providerQml.colorBackground;
            colorTextCell  : "white";
            onClickedCell  : {
                console.log("indexButton", indexButton);
                managerQml.setCurrentBook(indexButton)
                currentSlide = BibleEnums.GridChapters
            }
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }
}
