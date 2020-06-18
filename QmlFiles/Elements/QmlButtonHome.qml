import QtQuick 2.0

import "../Components" as MyComonents
import bible.namespace 1.0

MyComonents.QmlComponentButtonImage{
    width: Math.min(parent.width, parent.height) * 0.2
    height: width
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    pathImage: "qrc:/Icons/Resource/Icons/iconfinder_20-blue_address-home-house_4488794.svg"
    onClickedButton: currentSlide = BibleEnums.Title
    visible: currentSlide !== BibleEnums.Title

    function reancorButtonHome(slideEmiter){
        buttonHomeID.anchors.bottom = undefined
        buttonHomeID.anchors.right  = undefined
        buttonHomeID.anchors.bottom = slideEmiter.bottom
        buttonHomeID.anchors.right  = slideEmiter.right
        buttonHomeID.anchors.bottomMargin = buttonHomeID.width / 3.5
        buttonHomeID.anchors.rightMargin = buttonHomeID.height / 3.5
    }
}
