import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import "Components" as MyComonents
import bible.namespace 1.0

Item {
    anchors.fill: parent

    property int horizontalWidth: width * 0.8
    property int widthColumns: horizontalWidth / 2.3
    property int heightColumns: columnButtonsTestamentId.y * 0.38
    property real spacingColumns: columnOneId.height * 0.03
    property color colorButtons: "#292420"

    Text {
        id: textBibleId
        width: horizontalWidth / 2
        height: columnOneId.x / 1.2
        anchors.top: parent.top
        anchors.topMargin: columnOneId.x * 2.5
        anchors.horizontalCenter: parent.horizontalCenter
        fontSizeMode: Text.Fit
        minimumPixelSize: 10
        font.pixelSize: 120
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Dyuthi"
//        style: Text.Sunken; styleColor: "#AAAAAA"
//        style: Text.Raised; styleColor: "red"
//        style: Text.Outline; styleColor: "black"
//        color: "yellow"
        color: "#E5DF17"
        text: qsTr("BIBILE")
    }
    Column{
        id: columnOneId
        width: widthColumns
        height: heightColumns
        anchors.bottom: columnButtonsTestamentId.top
        anchors.bottomMargin: height * 0.2
        anchors.left: parent.left
        anchors.leftMargin: (parent.width - widthColumns * 2) / 2
        spacing: spacingColumns

        Repeater{
            id: repeaterColumnOneId
            model: [ "Друзья", "Планы чтения", "Закладки", "Поиск" ]
            MyComonents.QmlComponentButtonSingle{
                width: parent.width * 0.9
                height: parent.height / repeaterColumnOneId.count - columnOneId.spacing
                anchors.horizontalCenter: parent.horizontalCenter
                textButton: modelData
                colorBackgroundButton: colorButtons
            }
        }
    }

    Column{
        id: columnTwoId
        width: widthColumns
        height: heightColumns
        anchors.bottom: columnButtonsTestamentId.top
        anchors.bottomMargin: height * 0.2
        anchors.right: parent.right
        anchors.rightMargin: (parent.width -  widthColumns * 2) / 2
        spacing: spacingColumns

        Repeater{
            id: repeaterColumnTwoId
            model: [ "О приложении", "Текущий план", "Заметки", "Последнее" ]
            MyComonents.QmlComponentButtonSingle{
                width: parent.width * 0.9
                height: parent.height / repeaterColumnTwoId.count - columnTwoId.spacing
                anchors.horizontalCenter: parent.horizontalCenter
                textButton: modelData
                colorBackgroundButton: colorButtons
            }
        }
    }

    Row{
        id: columnButtonsTestamentId
        width: horizontalWidth
        height: parent.height * 0.07
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: height * 3
        spacing: width * 0.1


        Repeater{
            id: repeaterButtonsTestamentId
            model: [ "Старый завет", "Новый завет" ]
            MyComonents.QmlComponentButtonSingle{
                width: parent.width / 2 - columnButtonsTestamentId.spacing / repeaterButtonsTestamentId.count
                height: parent.height
                anchors.top: parent.top
                textButton: modelData
                boldText: true
                colorBackgroundButton: colorButtons

                onReleasedButton: {
                    isNewTestament = (textButton === repeaterButtonsTestamentId.itemAt(1).textButton);
                    currentSlide = BibleEnums.GridChapters;
                    console.log("textButton", textButton, isNewTestament);
                }
            }
        }
    }

}
