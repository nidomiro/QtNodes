
# Config
QT	+= core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = QtNodes
TEMPLATE = lib

INCLUDEPATH += $$PWD
INCLUDEPATH += . $$PWD/../share
DEPENDPATH += . $$PWD/../share
DESTDIR = $$PWD/../build

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)
}

DEFINES += QTNODES_LIBRARY

# Installs
headerFiles.path = $$PWD/../build
headerFiles.files = $$PWD/*.h
INSTALLS += headerFiles

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# Libs
LIBS += -L$$PWD/../build
#CONFIG(release, debug|release):LIBS += -lQtNodesShare
#CONFIG(debug, debug|release): LIBS += -lQtNodesShared

# Files
HEADERS += \
    utils/color_utils.h \
    utils/math_util.h \
    iowidgets/qstring_io_graphics_widget.h \
    abstract_io_graphics_widget.h \
    connector_graphics_widget.h \
    node_graphics_widget.h \
    node_grid_scene.h \
    node_grid_view.h \
    qtnodes_global.h

SOURCES += \
    iowidgets/qstring_io_graphics_widget.cpp \
    utils/color_utils.cpp \
    utils/math_util.cpp \
    abstract_io_graphics_widget.cpp \
    connector_graphics_widget.cpp \
    node_graphics_widget.cpp \
    node_grid_scene.cpp \
    node_grid_view.cpp
