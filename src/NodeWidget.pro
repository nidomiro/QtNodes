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
    nodewidget.h

SOURCES += \
    nodewidget.cpp




