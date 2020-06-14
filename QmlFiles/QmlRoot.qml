import QtQuick 2.0

import bible.namespace 1.0

Item {
    id: root

    property bool isNewTestament: true
    property int currentSlide: BibleSlide.Title



    QmlTitleSlide{
        anchors.fill: parent
    }
    Rectangle{
        id: rectTestID
        width: parent.width
        height: parent.height
        anchors.left: parent.right
        color: "red"
        opacity: 0.5
    }

    function reancorTestamentsSlides(){
        rectTestID.anchors.left = isNewTestament ? root.right : undefined
        rectTestID.anchors.right = isNewTestament ? undefined : root.left
    }


    states: [
        State {
            when: currentSlide === BibleSlide.Title;
            PropertyChanges { target: root; x: 0 }
        },
        State {
            when: currentSlide === BibleSlide.GridChapters;
            PropertyChanges { target: root; x: isNewTestament ? -width : +width }
            StateChangeScript { script: reancorTestamentsSlides(); }
        },
        State {
            name: BibleSlide.GridNumbersVerses; when: currentSlide === BibleSlide.GridNumbersVerses;
            PropertyChanges { target: root; x: -width }
            StateChangeScript { script: reancorTestamentsSlides(); }
        },
        State {
            name: BibleSlide.ListVerses; when: currentSlide === BibleSlide.ListVerses;
            PropertyChanges { target: root; x: -width }
            StateChangeScript { script: reancorTestamentsSlides(); }
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

}
