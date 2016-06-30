QT	+= core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TEMPLATE = lib

INCLUDEPATH += $$PWD
DESTDIR = $$PWD/../build

headerFiles.path = $$PWD/../build
headerFiles.files = $$PWD/*.h
INSTALLS += headerFiles

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)
 }

HEADERS += \
    nodewidget.h \
    abstractiowidget.h \
    iconnectionregister.h \
    nodegrid.h \
    nodescene.h \
    connection.h

SOURCES += \
    nodewidget.cpp \
    abstractiowidget.cpp \
    nodegrid.cpp \
    nodescene.cpp \
    connection.cpp

FORMS += \
    nodewidget.ui \
    abstractiowidget.ui




