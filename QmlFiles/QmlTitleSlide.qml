import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

Item {
    anchors.fill: parent
    property int numberButtons: 5
    Column{
        id: columnButtonsId
        anchors.fill: parent
        anchors.margins: Math.min(parent.width, parent.height) * 0.2
        spacing: 12

        Repeater{
            model: numberButtons
            Button{
                width: parent.width
                height: parent.height / numberButtons
                opacity: 0.5
                background: Rectangle{
                    anchors.fill: parent
                    color: "blue"
                    border.width: 1
//                    border.width: control.activeFocus ? 21 : 1
                    radius: Math.min(width, height) * 0.05
                    opacity: 0.5
                }
            }
        }
    }
}
