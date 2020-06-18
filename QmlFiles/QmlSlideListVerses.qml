import QtQuick 2.0

import "Components" as MyComonents
import ModelViewQml 1.0
import bible.namespace 1.0

Item {

    MyComonents.QmlComponentGridViewVerses{
        anchors.fill: parent
        listModelObj: ModelView {
            list: listVersesQml
        }
        colorCell      : providerQml.colorBackground;
        colorTextCell  : "white";
        onClickedCell  : {
            console.log("valueCell", valueCell);
//            managerQml.setCurrentChapter(valueCell)
//            currentSlide = BibleEnums.ListVerses
        }
    }

}
