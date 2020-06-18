import QtQuick 2.12
import QtQml 2.12
import QtGraphicalEffects 1.0

import ModelViewQml 1.0

Item{
    signal clickedCell(string valueCell);
    signal movementStartedView();
    signal movementEndedView();
    property var listModelObj                   ;
    property color colorCell           : "white";
    property color colorTextCell       : "white";
    property int maxQuantityCells      : 4;
    property int minQuantityCells      : 4;


    GridView {
        id: gridViewId
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
        x: horizontalSpacing / 2
        cellWidth: width / currentQuantityCells;
        cellHeight: cellWidth * 0.45;
        clip: true
        model: listModelObj
        delegate: componentDelegate
        focus: true

        property int currentQuantityCells: maxQuantityCells;
        property real horizontalSpacing: cellWidth * 0.04;
        property real verticalSpacing: cellHeight * 0.2;

        add: Transition {
            NumberAnimation { properties: "x,y"; from: parent.width / 5; easing.type: Easing.OutBounce; duration: 1000 }
        }
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; from: parent.width / 5; duration: 1000 }
        }

        onMovementStarted: {
            movementStartedView();
        }
        onMovementEnded: {
            movementEndedView();
        }
    }

    Component {
        id: componentDelegate

        Item {
            id: itemCentreGridId
            width: gridViewId.cellWidth - gridViewId.horizontalSpacing;
            height: gridViewId.cellHeight - gridViewId.verticalSpacing;

//            Rectangle{
//                anchors.fill: parent
//                color: colorCell
//                border.color: colorTextCell
//                radius: parent.width * 0.05
//            }
//            Text {
//                anchors.fill: parent
//                minimumPixelSize: 10;
//                font.pixelSize: width * 0.155
//                fontSizeMode: Text.Fit;
//                wrapMode: Text.WordWrap
//                color: colorTextCell
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//                text: model.textModel
//            }
            QmlComponentButtonSingle{
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
                textButton: model.textModel
                colorBackgroundButton: colorCell
                onClickedButton: clickedCell(model.textModel)
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
