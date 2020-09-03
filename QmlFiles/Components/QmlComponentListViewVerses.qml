import QtQuick 2.12
import QtQml 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

import ModelViewQml 1.0

Item{
    id: listViewVersesID

    signal movementStartedView();
    signal movementEndedView();
    signal footerClicked();
    property var listModelObj: ListModel;
    property string headerNameBook: "headerNameBook"


    ListView {
        id: listViewID
        anchors.fill: parent
        focus: true
        clip: true
        spacing: parent.height * 0.014
        model: listModelObj
        delegate: componentDelegate
        headerPositioning: ListView.InlineHeader
        header: Item {
            id: headerItem
            width: parent.width
            height: listViewVersesID.height / 10
            Text {
                anchors.fill: parent
                anchors.margins: Math.min(parent.width, parent.height) * 0.2
                minimumPixelSize: 10
                font.pixelSize: 222
                fontSizeMode: Text.Fit
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                color: "red"
                text: headerNameBook
            }
        }
        footer: Item{
            id: footerItem
            width: parent.width
            height: listViewVersesID.height / 10
//            QmlComponentButtonText{
//                anchors.fill: parent
//                anchors.horizontalCenter: parent.horizontalCenter
//                textButton: isNewTestament ? "<<<" : ">>>"
//                colorBackgroundButton: "transparent"
//                colorBorderButton: "transparent"
//                colorTextButton: "red"
//                onClickedButton: footerClicked()
//            }
        }

        onAddChanged: {
            console.log("onAddTransitionChanged");
        }
        onMovementStarted: {
            movementStartedView();

        }
        onMovementEnded: {
            movementEndedView();
        }
        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
            NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
        }
    }

    Component {
        id: componentDelegate

        Item {
            width: listViewVersesID.width
            height: textVerse.contentHeight

            //            Text {
            //                id: textVerse
            //                width: parent.width * 0.96
            //                height: parent.height
            //                anchors.horizontalCenter: parent.horizontalCenter
            //                minimumPixelSize: 18
            //                font.pixelSize: 222
            //                fontSizeMode: Text.Fit
            //                wrapMode: Text.WordWrap
            //                color: "white"
            //                text: model.textModel
            //            }
            Text {
                id: textVerse
                width: parent.width * 0.96
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 18
                wrapMode: Text.WordWrap
                color: "white"
                text: getNumberVerse(model.index) + model.textModel
                function getNumberVerse(index){
                    return "<font color=\"green\">" + Number(index + 1) + ". </font>"
                }
            }
            Rectangle{
                width: parent.width
                height: parent.height + 6
                anchors.centerIn: textVerse
                //                border.color: "black"
                border.color: "white"
                border.width: 1
                radius: 5
                color: mouse.pressed ? "red" : "grey"
                opacity: 0.15
                MouseArea{ id: mouse; anchors.fill: parent }
            }

            //            Component.onCompleted: console.log("gridViewId.horizontalSpacing", gridViewId.horizontalSpacing);
        }
        //        Component.onCompleted: {
        //            var quantityPositions = model.quantityPositions < minQuantityCells ? minQuantityCells : model.quantityPositions;
        //            quantityPositions = quantityPositions > maxQuantityCells ? maxQuantityCells : quantityPositions;
        //            gridViewId.currentQuantityCells = quantityPositions;
        //        }
    }

}
