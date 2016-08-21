
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
SOURCES += node_port_adress.cpp \
    connection.cpp

HEADERS += node_port_adress.h\
        qtnodesshare_global.h \
    connection.h \
    i_connection_register.h
