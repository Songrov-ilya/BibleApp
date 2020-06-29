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
            console.log("indexButton", indexButton);
//            managerQml.setCurrentChapter(indexButton)
//            currentSlide = BibleEnums.ListVerses
        }
    }

}
