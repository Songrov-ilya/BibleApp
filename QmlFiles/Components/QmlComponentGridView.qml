import QtQuick 2.12
import QtQml 2.12
import QtGraphicalEffects 1.0

Item{
    signal clickedMarker(string marker);
    signal movementStartedView();
    signal movementEndedView();
//    property var listModelObj          : ListModel;
    property color colorCell           : "white";
    property color colorCircleIconCell : "white";
    property int maxQuantityCells      : 8;
    property int minQuantityCells      : 5;


    GridView {
        id: gridViewId
        anchors.fill: parent
        cellWidth: width / currentQuantityCells;
        cellHeight: cellWidth * 1.65;
        clip: true
        model: listModelObj
        delegate: componentDelegate
        focus: true

        property int currentQuantityCells: maxQuantityCells;

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
            width: gridViewId.cellWidth;
            height: gridViewId.cellHeight;

            Rectangle{
                anchors.fill: parent
                color: "red"
                opacity: 0.5
            }
        }
    }

}
