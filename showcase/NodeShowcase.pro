
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeShowcase
TEMPLATE = app

CONFIG += c++14

INCLUDEPATH += . $$PWD/../src
DEPENDPATH += . $$PWD/../src


LIBS += -L$$PWD/../build


CONFIG(release, debug|release):LIBS += -lNodeWidget
CONFIG(debug, debug|release): LIBS += -lNodeWidgetd

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui