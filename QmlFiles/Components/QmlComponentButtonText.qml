import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: componentButtonTextId

    signal          releasedButton();
    signal          clickedButton();
    property string textButton              : ""
    property bool   enabledButton           : true
    property color  colorBackgroundButton   : "#524E4A"
    property color  colorTextButton         : "white"
    property color  colorBorderButton       : "white"
    property int    fontPixelSize           : componentButtonTextId.width * 0.12
    property bool   boldText                : false


    Button{
        id: buttonTextId
        anchors.fill: parent
        opacity: 1.0
        enabled: enabledButton;
        background: Rectangle {
            radius: parent.width * 0.05
            color: colorBackgroundButton
            border.color: colorBorderButton
        }
        contentItem: Text {
            text: textButton
            minimumPixelSize: 10;
            font.pixelSize: fontPixelSize
            font.bold: boldText
            fontSizeMode: Text.Fit;
            wrapMode: Text.WordWrap
            color: colorTextButton
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
         }

        states: [
            State {
                name: "PRESSED"; when: buttonTextId.pressed
                PropertyChanges { target: buttonTextId; opacity: 0.5 }
            },
            State {
                name: "RELEASED"; when: !buttonTextId.pressed
                PropertyChanges {  target: buttonTextId; opacity: 1.0 }
            }
        ]
        transitions: [
            Transition {
                from: "PRESSED"
                to: "RELEASED"
                PropertyAnimation { target: buttonTextId; property: "scale"; easing.type: Easing.OutExpo; duration: 500}
            },
            Transition {
                from: "RELEASED"
                to: "PRESSED"
                PropertyAnimation { target: buttonTextId; property: "scale"; easing.type: Easing.OutExpo; duration: 500}
            }
        ]

        onReleased: releasedButton();
        onClicked:  clickedButton();
    }
}
