
# Config
QT       -= gui

CONFIG += c++14

TARGET = QtNodesShared
TEMPLATE = lib

INCLUDEPATH += $$PWD
DESTDIR = $$PWD/../build

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)
}

DEFINES += QTNODESSHARED_LIBRARY

# Installs
headerFiles.path = $$PWD/../build
headerFiles.files = $$PWD/*.h
INSTALLS += headerFiles

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# Files
SOURCES += \
    connection.cpp \
    node_port_address.cpp \
    node_port_info.cpp \
    node_port_io_type.cpp

HEADERS +=\
    connection.h \
    i_node_impl.h \
    node_port_address.h \
    node_port_info.h \
    i_node_state_listener.h \
    i_node_grid_impl.h \
    i_node_grid_state_listener.h \
    node_port_io_type.h \
    qtnodesshared_global.h
