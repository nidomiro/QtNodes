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
    iconnectionregister.h \
    connection.h \
    nodegridview.h \
    nodegridscene.h \
    nodegraphicswidget.h \
    abstractiographicswidget.h

SOURCES += \
    connection.cpp \
    nodegridview.cpp \
    nodegridscene.cpp \
    nodegraphicswidget.cpp \
    abstractiographicswidget.cpp

FORMS += \
    abstractiowidget.ui




