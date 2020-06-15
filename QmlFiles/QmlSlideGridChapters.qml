import QtQuick 2.0

import "Components" as MyComonents
import bible.namespace 1.0

Item {
    id: gridChaptersID

    Rectangle{
        anchors.fill: parent
        color: "blue"
        opacity: 0.5
    }
//    MyComonents.QmlComponentGridView{
//        anchors.fill: parent
//    }
    MouseArea{
        anchors.fill: parent
        anchors.margins: parent.width / 5
        onClicked: currentSlide = BibleEnums.GridNumbersVerses;
    }
}
