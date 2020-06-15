import QtQuick 2.0

import bible.namespace 1.0

Item {

    Rectangle{
        anchors.fill: parent
        color: "green"
        opacity: 0.5
    }
    MouseArea{
        anchors.fill: parent
        anchors.margins: parent.width / 5
        onClicked: currentSlide = BibleEnums.ListVerses;
    }
}
