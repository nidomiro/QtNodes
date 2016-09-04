
# Config
QT	+= core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = QtNodes
TEMPLATE = lib

INCLUDEPATH += $$PWD
INCLUDEPATH += . $$PWD/..
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
CONFIG(release, debug|release):LIBS += -lQtNodesShared
CONFIG(debug, debug|release): LIBS += -lQtNodesSharedd

# Files
HEADERS += \
    utils/color_utils.h \
    utils/math_util.h \
    node_grid_scene.h \
    node_grid_view.h \
    qtnodes_global.h \
    node_port_view_factory.h \
    abstract_node_port_view.h \
    iowidgets/qstring_node_port_view.h \
    node_view.h \
    node_port_connector_view.h \
    node_connection_view.h

SOURCES += \
    utils/color_utils.cpp \
    utils/math_util.cpp \
    node_grid_scene.cpp \
    node_grid_view.cpp \
    node_port_view_factory.cpp \
    iowidgets/qstring_node_port_view.cpp \
    abstract_node_port_view.cpp \
    node_view.cpp \
    node_port_connector_view.cpp \
    node_connection_view.cpp
