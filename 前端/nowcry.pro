#-------------------------------------------------
#
# Project created by QtCreator 2020-07-01T11:48:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nowcry
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    x_entrophy.cpp \
    x_filerw.cpp \
    x_node.cpp \
    x_tree.cpp \
    x_watermelon.cpp \
    pictur.cpp

HEADERS += \
        widget.h \
    x_entrophy.h \
    x_filerw.h \
    x_node.h \
    x_tree.h \
    x_watermelon.h \
    x_mhead.h \
    qt_head.h \
    pictur.h

FORMS += \
        widget.ui

RESOURCES += \
    res.qrc \
    w.qrc
