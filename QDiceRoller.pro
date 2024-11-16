QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix {
    CONFIG += c++2b
}
win32 {
    CONFIG += c++2b
    QMAKE_CXXFLAGS += /bigobj
}

INCLUDEPATH += $$PWD/deps

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    diceroll.cpp \
    dicerolltracker.cpp \
    dicerollwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qclickablelabel.cpp

HEADERS += \
    dice_roll.h \
    diceroll.h \
    dicerolltracker.h \
    dicerollwidget.h \
    exprtk_methods.hpp \
    exprtkengine.hpp \
    exprtkexceptions.hpp \
    helper_functions.hpp \
    mainwindow.h \
    qclickablelabel.h \
    qdmswidget.hpp

FORMS += \
    dicerollwidget.ui \
    mainwindow.ui

TRANSLATIONS += \
    QDiceRoller_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QDiceRoller.pro.user

RESOURCES += \
    res.qrc
