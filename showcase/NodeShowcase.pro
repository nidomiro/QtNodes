
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeShowcase
TEMPLATE = app

CONFIG += c++14

INCLUDEPATH += . $$PWD/..
DEPENDPATH += . $$PWD/../src
INCLUDEPATH += . $$PWD/../src
DEPENDPATH += . $$PWD/../share


LIBS += -L$$PWD/../build

# QtNodes lib dynamic linking
CONFIG(release, debug|release):LIBS += -lQtNodes
CONFIG(debug, debug|release): LIBS += -lQtNodesd

# QtNodesShare lib dynamic linking
CONFIG(release, debug|release):LIBS += -lQtNodesShared
CONFIG(debug, debug|release): LIBS += -lQtNodesSharedd

SOURCES += main.cpp\
        mainwindow.cpp \
    stringtestnodeimpl.cpp \
    test_node_grid_impl.cpp

HEADERS  += mainwindow.h \
    stringtestnodeimpl.h \
    test_node_grid_impl.h

FORMS    += mainwindow.ui
