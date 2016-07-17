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
    abstractiographicswidget.h \
    utils/colorutils.h \
    utils/mathutil.h \
    iowidgets/qstringiographicswidget.h

SOURCES += \
    connection.cpp \
    nodegridview.cpp \
    nodegridscene.cpp \
    nodegraphicswidget.cpp \
    abstractiographicswidget.cpp \
    utils/colorutils.cpp \
    utils/mathutil.cpp \
    iowidgets/qstringiographicswidget.cpp

FORMS += \
    abstractiowidget.ui




