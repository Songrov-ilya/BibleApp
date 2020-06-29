import QtQuick 2.0

import "Components" as MyComonents
import ModelViewQml 1.0
import bible.namespace 1.0

Item {
    id: gridChaptersID

    MyComonents.QmlComponentGridView{
        anchors.fill: parent
        listModelObj: ModelView {
            list: listChaptersQml
        }
        colorCell      : providerQml.colorBackground;
        colorTextCell  : "white";
        onClickedCell  : {
            console.log("indexButton", indexButton);
            managerQml.setCurrentChapter(indexButton)
            currentSlide = BibleEnums.ListVerses
        }
    }
}
