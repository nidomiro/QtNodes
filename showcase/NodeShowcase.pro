
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeShowcase
TEMPLATE = app

CONFIG += c++14

INCLUDEPATH += . $$PWD/../src
DEPENDPATH += . $$PWD/../src
INCLUDEPATH += . $$PWD/../share
DEPENDPATH += . $$PWD/../share


LIBS += -L$$PWD/../build

# QtNodes lib dynamic linking
CONFIG(release, debug|release):LIBS += -lQtNodes
CONFIG(debug, debug|release): LIBS += -lQtNodesd

# QtNodesShare lib dynamic linking
CONFIG(release, debug|release):LIBS += -lQtNodesShare
CONFIG(debug, debug|release): LIBS += -lQtNodesShared

SOURCES += main.cpp\
        mainwindow.cpp \
    stringtestnodeimpl.cpp

HEADERS  += mainwindow.h \
    stringtestnodeimpl.h

FORMS    += mainwindow.ui
