import QtQuick 2.0

import "../Components" as MyComonents
import bible.namespace 1.0

Item{
    id: footerMenu

    property real footerHeight: parent.height / 20

    width: parent.width
    height: footerHeight
    anchors.bottom: parent.bottom
    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.5
    }
}
