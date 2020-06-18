import QtQuick 2.0

import bible.namespace 1.0
import "Elements" as MyElements

Item {
    id: main

    property bool isNewTestament: true
    property int currentSlide: BibleEnums.Title


    QmlSlideTitle{
        id: slideTitleID
        anchors.fill: parent
    }

    QmlSlideGridChapters{
        id: slideGridChaptersID
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
    }

    QmlSlideGridBooks{
        id: slideGridBooksID
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
    }

    QmlSlideListVerses{
        id: slideListVersesID
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
    }

    MyElements.QmlButtonHome {
        id: buttonHomeID
    }

    function reancorTestamentsSlides(slideEmiter){
        var arrSlides = [slideTitleID, slideGridBooksID, slideGridChaptersID, slideListVersesID];
        for (var i = 1; i < arrSlides.length; i++) {
            arrSlides[i].anchors.left  = undefined;
            arrSlides[i].anchors.right = undefined;
            arrSlides[i].anchors.left  = isNewTestament ? arrSlides[i-1].right : undefined
            arrSlides[i].anchors.right = isNewTestament ? undefined : arrSlides[i-1].left
        }
        buttonHomeID.reancorButtonHome(slideEmiter)
    }


    states: [
        State {
            when: currentSlide === BibleEnums.Title;
            PropertyChanges { target: main; x: 0 }
        },
        State {
            when: currentSlide === BibleEnums.GridBooks;
            PropertyChanges { target: main; x: isNewTestament ? -width : +width }
            StateChangeScript { script: reancorTestamentsSlides(slideGridBooksID); }
            StateChangeScript { script: managerQml.fillListBooks(); }
        },
        State {
            when: currentSlide === BibleEnums.GridChapters;
            PropertyChanges { target: main; x: isNewTestament ? -width * 2 : +width * 2 }
            StateChangeScript { script: reancorTestamentsSlides(slideGridChaptersID); }
            StateChangeScript { script: managerQml.fillListChapters(); }
        },
        State {
            when: currentSlide === BibleEnums.ListVerses;
            PropertyChanges { target: main; x: isNewTestament ? -width * 3 : +width * 3 }
            StateChangeScript { script: reancorTestamentsSlides(slideListVersesID); }
            StateChangeScript { script: managerQml.fillListVerses(); }
        }
    ]
    transitions: Transition {
        NumberAnimation { properties: "x,y"; duration: 1200; easing.type: Easing.OutQuad }
    }

    MouseArea{
        anchors.fill: parent
        propagateComposedEvents: true
        onPressed: mouse.accepted = false
        onDoubleClicked: Qt.quit()
    }

    Component.onCompleted: reancorTestamentsSlides(slideTitleID);

}
