
# Config
QT       -= gui

CONFIG += c++14

TARGET = QtNodesShare
TEMPLATE = lib

INCLUDEPATH += $$PWD
DESTDIR = $$PWD/../build

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)
}

DEFINES += QTNODESSHARE_LIBRARY

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
    node_port_address.cpp

HEADERS +=\
        qtnodesshare_global.h \
    connection.h \
    i_connection_register.h \
    i_node_impl.h \
    node_port_address.h
