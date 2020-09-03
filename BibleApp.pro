QT      += core gui
QT      += qml
QT      += quick
QT      += quickwidgets
QT      += quickcontrols2
QT      += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG(debug, debug | release) {
    TARGET = BibleApp
    QT       += network
}
CONFIG(release, debug | release) {
    TARGET = Bible
    RESOURCES += \
        ResourceFiles.qrc
}

CONFIG += c++11
QMAKE_LFLAGS += -Wall -fPIC -no-pie

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Achitecture/Bible.cpp \
    Achitecture/Book.cpp \
    Achitecture/ChapterText.cpp \
    Achitecture/Photo.cpp \
    Adjutants/Content.cpp \
    Adjutants/Data.cpp \
    Adjutants/FileWorker.cpp \
    Extensions/Search.cpp \
    MainApplicationWindow.cpp \
    Manager.cpp \
    Provider/ProviderQml.cpp \
    View/BibleList.cpp \
    View/ModelView.cpp \
    main.cpp

HEADERS += \
    Achitecture/Bible.h \
    Achitecture/Book.h \
    Achitecture/ChapterText.h \
    Achitecture/Photo.h \
    Adjutants/Content.h \
    Adjutants/Data.h \
    Adjutants/FileWorker.h \
    Extensions/Search.h \
    MainApplicationWindow.h \
    Manager.h \
    Provider/ProviderQml.h \
    View/BibleList.h \
    View/ModelView.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QmlFiles/Components/QmlComponentGridView.qml \
    QmlFiles/Components/QmlComponentListViewVerses.qml \
    QmlFiles/Elements/QmlSidePanel.qml \
    QmlFiles/Elements/QmlToolBar.qml \
    QmlFiles/QmlMain.qml \
    QmlFiles/QmlSlideGridBooks.qml \
    QmlFiles/QmlSlideGridChapters.qml \
    QmlFiles/QmlSlideListVerses.qml \
    QmlFiles/QmlSlideSearch.qml \
    QmlFiles/rootQml.qml


INCLUDEPATH += \
    Achitecture \
    Adjutants \
    Extensions \
    Provider \
    View

