QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    arrowtower.cpp \
    bullet.cpp \
    enemy.cpp \
    gamewindow.cpp \
    lostwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    middlewindow.cpp \
    plistreader.cpp \
    singlecao.cpp \
    tighttowerposi.cpp \
    tower.cpp \
    towerposition.cpp \
    waypoint.cpp \
    winwindow.cpp

HEADERS += \
    arrowtower.h \
    bullet.h \
    enemy.h \
    gamewindow.h \
    lostwindow.h \
    mainwindow.h \
    middlewindow.h \
    plistreader.h \
    singlecao.h \
    tighttowerposi.h \
    tower.h \
    towerposition.h \
    utility.h \
    waypoint.h \
    winwindow.h

FORMS += \
    gamewindow.ui \
    lostwindow.ui \
    mainwindow.ui \
    middlewindow.ui \
    winwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
