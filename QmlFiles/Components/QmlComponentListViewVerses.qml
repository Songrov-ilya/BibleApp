import QtQuick 2.12
import QtQml 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12

import ModelViewQml 1.0

Item{

    signal movementStartedView();
    signal movementEndedView();
    property var listModelObj: ListModel;


    ListView {
        id: itemListId
        clip: true
        anchors.fill: parent
        model: listModelObj
        delegate: componentDelegate
        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.DragAndOvershootBounds
        //        ScrollBar.vertical: ScrollBar {
        //            id: scrollDelegat
        //            width: itemListId.contentHeight > itemListId.height ? parent.width * 0.026 : 0
        //            active: true
        //            policy: itemListId.contentHeight > itemListId.height ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded

        //        }
        rebound: Transition {
            NumberAnimation {
                properties: "x,y"
                duration: 1000
                easing.type: Easing.OutBounce
            }
        }
        spacing: parent.height * 0.005
        focus: true

        //                onCountChanged: {
        //                    var newIndex = itemListId.count - 1 // last index
        //                    itemListId.positionViewAtEnd()
        //                    itemListId.currentIndex = newIndex
        //                }


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
            width: screenWidth * 0.95
            height: textVerse.contentHeight
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: textVerse
                anchors.fill: parent
//                anchors.margins: 11
                minimumPixelSize: 18
                font.pixelSize: 222
                fontSizeMode: Text.Fit
                wrapMode: Text.WordWrap
                color: "white"
                //                horizontalAlignment: Text.AlignHCenter
                //                verticalAlignment: Text.AlignVCenter
                text: model.textModel
                Rectangle{
                    anchors.fill: parent
    //                anchors.margins: Math.min(width, height) * 0.2
                    border.color: "black"
                    border.width: 1
                    radius: 5
                    color: "transparent"
                    //                opacity: 0.5

                }
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
