#-------------------------------------------------
#
# Project created by QtCreator 2013-06-15T20:52:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DivListTextEdit
TEMPLATE = app

INCLUDEPATH += src/

SOURCES += src/main.cpp\
           src/MainWindow.cpp \
    src/DivListTextEdit.cpp

HEADERS  += src/MainWindow.h \
    src/DivListTextEdit.h

FORMS    += src/MainWindow.ui

RESOURCES += \
    resources/resources.qrc
