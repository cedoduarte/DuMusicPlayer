#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T21:12:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuMusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    PositionForm.cpp

HEADERS  += MainWindow.h \
    PositionForm.h

FORMS    += MainWindow.ui \
    PositionForm.ui

QMAKE_CXXFLAGS += -std=gnu++14

RESOURCES += \
    res.qrc

RC_ICONS = icon.ico
