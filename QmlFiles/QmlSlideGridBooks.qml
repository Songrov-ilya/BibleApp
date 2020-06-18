import QtQuick 2.0

import "Components" as MyComonents
import ModelViewQml 1.0
import bible.namespace 1.0

Item {

    MyComonents.QmlComponentGridView{
        anchors.fill: parent
        listModelObj: ModelView {
            list: listBooksQml
        }
        colorCell      : providerQml.colorBackground;
        colorTextCell  : "white";
        onClickedCell  : {
            console.log("valueCell", valueCell);
            managerQml.setCurrentBook(valueCell)
            currentSlide = BibleEnums.GridChapters
        }
    }
//    MouseArea{
//        anchors.fill: parent
//        anchors.margins: parent.width / 5
//        onClicked: currentSlide = BibleEnums.GridChapters;
//    }
}
