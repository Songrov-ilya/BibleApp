QT       += core gui
QT       += qml
QT       += quick
QT       += quickwidgets
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bible

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
    Achitecture/Chapter.cpp \
    Achitecture/Photo.cpp \
    Achitecture/Skeleton.cpp \
    Extensions/Content.cpp \
    Extensions/Data.cpp \
    Extensions/Search.cpp \
    Helper.cpp \
    Manager.cpp \
    Provider/ProviderQml.cpp \
    View/BibleList.cpp \
    View/ModelView.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Achitecture/Bible.h \
    Achitecture/Book.h \
    Achitecture/Chapter.h \
    Achitecture/Photo.h \
    Achitecture/Skeleton.h \
    Extensions/Content.h \
    Extensions/Data.h \
    Extensions/Search.h \
    Helper.h \
    Manager.h \
    Provider/ProviderQml.h \
    View/BibleList.h \
    View/ModelView.h \
    mainwindow.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QmlFiles/Components/QmlComponentButtonImage.qml \
    QmlFiles/Components/QmlComponentButtonSingle.qml \
    QmlFiles/Components/QmlComponentGridView.qml \
    QmlFiles/Components/QmlComponentGridViewVerses.qml \
    QmlFiles/Elements/QmlButtonHome.qml \
    QmlFiles/QmlMain.qml \
    QmlFiles/QmlSlideGridBooks.qml \
    QmlFiles/QmlSlideGridChapters.qml \
    QmlFiles/QmlSlideListVerses.qml \
    QmlFiles/QmlSlideTitle.qml \
    QmlFiles/rootQml.qml

RESOURCES += \
    ResourceFiles.qrc
