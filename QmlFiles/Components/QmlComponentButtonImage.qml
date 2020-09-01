import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0

Button{
    id: buttonId
    anchors.fill: parent
    opacity: 0.73
    background: Rectangle {
        opacity: 0
    }

    property string pathImage: ""

    Image {
        id: iconId
        width: parent.width < parent.height ? parent.width : parent.height
        height: width
        anchors.centerIn: parent
        source: pathImage
        sourceSize.width: width
        sourceSize.height: height
        fillMode: Image.PreserveAspectFit
        smooth: true
        scale: 1
        transformOrigin: Item.Center
        OpacityMask {
            anchors.fill: iconId
            source: iconId
            maskSource: iconId
        }
    }


    states: [
        State {
            name: "PRESSED"
            PropertyChanges { target: iconId; scale: 0.8 }
            PropertyChanges { target: buttonId; opacity: 0.3 }
        },
        State {
            name: "RELEASED"
            PropertyChanges {  target: iconId; scale: 1 }
            PropertyChanges {  target: buttonId; opacity: 0.73 }
        }
    ]
    transitions: [
        Transition {
            from: "PRESSED"
            to: "RELEASED"
            PropertyAnimation { target: iconId; property: "scale"; easing.type: Easing.OutExpo; duration: 500}
        },
        Transition {
            from: "RELEASED"
            to: "PRESSED"
            PropertyAnimation { target: iconId; property: "scale"; easing.type: Easing.OutExpo; duration: 500}
        }
    ]

    onDoubleClicked: doubleClickedButton();
    onPressed: buttonId.state = "PRESSED"
    onReleased: {
        buttonId.state = "RELEASED"
        releasedButton();
    }
    onClicked: clickedButton()
}
